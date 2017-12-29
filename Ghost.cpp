//
// Created by andys on 01.12.17.
//

#include <iostream>
#include <map>
#include "Ghost.h"
#include <random>
#define CELL_WIDTH 25
#define GRAY_OFFSET 100
#define PINK_OFFSET 200
#define LEFT_PAIR std::pair<short, short>(-1, 0)
#define RIGHT_PAIR std::pair<short, short>(1, 0)
#define UP_PAIR std::pair<short, short>(0, -1)
#define DOWN_PAIR std::pair<short, short>(0, 1)
#define DEPLOY_TIME 5000
#define WAIT_TIME 2000
#define EAT_TIME 10000

enum MODE {
    ATTACK, DEPLOY, RETREAT, RUN, EXIT
};

enum COLOR {
    CYAN, PINK, RED, YELLOW
};

Ghost::Ghost(QRect r, int color, MovingSprite *pacman) : MovingSprite(r, color) {
    this->pacman = pacman;
    internalTimer = new QTimer();
    internalTimer->setSingleShot(true);

    QString path("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/");
    switch (color) {
        case PINK:
            path.append("pink");
            break;
        case RED:
            path.append("red");
            break;
        case CYAN:
            path.append("cyan");
            break;
        case YELLOW:
            path.append("yellow");
            break;
        default:
            break;
    }
    sprites[ATTACK].load(path);
    sprites[RETREAT].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/eyes.png");
    sprites[RUN].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/grey.png");

    mode = EXIT;
    restoreInitialDirection();
    exitSquare = {350, 275};
    originalPosition = topLeft();
    if (color == RED) {
        targetCorner = QPoint(25, 700);
        internalTimer->start(WAIT_TIME);
    }
    else if (color == CYAN) {
        targetCorner = QPoint(50, 50);
        internalTimer->start(WAIT_TIME * 2);
    }
    else if (color == PINK) {
        targetCorner = QPoint(700, 25);
        internalTimer->start(WAIT_TIME * 3);
    }
    else if (color == YELLOW) {
        targetCorner = QPoint(700, 700);
        internalTimer->start(WAIT_TIME * 4);
    }
    retreatTarget = exitSquare;
}

void Ghost::restoreInitialDirection() {
    if (topLeft().x() < 375) {
        currentDirection = nextDirection = RIGHT_PAIR;
    }
    else {
        currentDirection = nextDirection = LEFT_PAIR;
    }
}

void Ghost::changeDirection(const QRegion &walls, const QRegion &gate) {

    std::list<std::pair<short, short>> possibleDirections;
    calculatePossibleDirections(possibleDirections, walls, gate);
    bool foundUp = findDirection(possibleDirections, UP_PAIR);
    bool foundDown = findDirection(possibleDirections, DOWN_PAIR);
    bool foundLeft = findDirection(possibleDirections, LEFT_PAIR);
    bool foundRight = findDirection(possibleDirections, RIGHT_PAIR);
    std::vector<std::pair<short, short>> vector;
    std::vector<int> vectorOfML;
    vectorOfML.reserve(vector.size());
    switch (mode) {
        case DEPLOY:
            resolveDirectionOverCommonAxisTowards(targetCorner, foundDown, foundLeft, foundRight, possibleDirections,
                                                  foundUp);
            vector = {std::begin(possibleDirections), std::end(possibleDirections)};
            resolveDirection(vector, vectorOfML, targetCorner);
            if (!internalTimer->isActive())
                mode = ATTACK;
            break;
        case ATTACK:
            if (color == RED || color == YELLOW || color == PINK) {
                resolveDirectionOverCommonAxisTowards(pacman->topLeft(), foundDown, foundLeft, foundRight, possibleDirections,
                                                      foundUp);
                vector = {std::begin(possibleDirections), std::end(possibleDirections)};
                int isWithinPinkOffset = (topLeft() - pacman->topLeft()).manhattanLength() <= PINK_OFFSET;
                if (color == RED || (color == PINK && isWithinPinkOffset)) {
                    resolveDirection(vector, vectorOfML, pacman->topLeft());
                }
                else if (color == PINK) {
                    resolveDirection(vector, vectorOfML, {CELL_WIDTH, CELL_WIDTH});
                }
                else if (color == YELLOW) {
                    resolveDirection(vector, vectorOfML, QPoint(pacman->currentDirection.first * GRAY_OFFSET, pacman->currentDirection.second * GRAY_OFFSET));
                }
            }
            else if (color == CYAN) {
                chooseRandomDirection(possibleDirections);
            }
            break;
        case RETREAT:
            resolveDirectionOverCommonAxisTowards(retreatTarget, foundDown, foundLeft, foundRight, possibleDirections,
                                                  foundUp);
            vector = {std::begin(possibleDirections), std::end(possibleDirections)};
            resolveDirection(vector, vectorOfML, retreatTarget);
            if (topLeft() == originalPosition) {
                mode = EXIT;
                speed = 1;
                shouldMove = false;
                restoreInitialDirection();
                internalTimer->start(WAIT_TIME);
            }
            if (topLeft() == exitSquare) {
                retreatTarget = originalPosition;
                nextDirection = DOWN_PAIR;
            }
            break;
        case RUN:
            possibleDirections.push_back(currentDirection);
            chooseRandomDirection(possibleDirections);
            if (!internalTimer->isActive()) {
                mode = ATTACK;
                pacman->canBeEaten = true;
            }
            break;
        case EXIT:
            resolveDirectionOverCommonAxisTowards(exitSquare, foundDown, foundLeft, foundRight, possibleDirections, foundUp);
            vector = {std::begin(possibleDirections), std::end(possibleDirections)};
            resolveDirection(vector, vectorOfML, exitSquare);
            if (topLeft() == exitSquare) {
                mode = DEPLOY;
                internalTimer->start(DEPLOY_TIME);
            }
            if (!internalTimer->isActive())
                shouldMove = true;
            break;
        default:
            break;
    }

    if (currentDirection != std::pair<short, short>(0, 0)) {
        QRect d = translated(nextDirection.first, nextDirection.second);
        if (walls.intersects(d)) {
            return;
        }
        currentDirection = nextDirection;
    }
}

void Ghost::chooseRandomDirection(std::list<std::pair<short, short>> &possibleDirections) {
    std::__1::vector<std::__1::pair<short, short>> vector {begin(possibleDirections), end(possibleDirections)};
    shuffle(vector.begin(), vector.end(), std::__1::mt19937(std::__1::random_device()()));
    if (vector.empty())
        nextDirection =  {currentDirection.first * -1, currentDirection.second * -1};
    else
        nextDirection = vector[0];
}

void Ghost::resolveDirection(const std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML,
                             const QPoint offset) {
    for (auto &direction: vector) {
        vectorOfML.push_back((translated(direction.first, direction.second).topLeft() - offset).manhattanLength());
    }
    sort(vectorOfML.begin(), vectorOfML.end());

    for (auto &direction: vector) {
        if ((translated(direction.first, direction.second).topLeft() - offset).manhattanLength() == vectorOfML[0]) {
            nextDirection = direction;
            break;
        }
    }
}

void Ghost::calculatePossibleDirections(std::list<std::pair<short, short>> &possibleDirections, const QRegion &walls,
                                        const QRegion &gate) {
    possibleDirections.insert(possibleDirections.begin(), DOWN_PAIR);
    possibleDirections.insert(possibleDirections.begin(), RIGHT_PAIR);
    possibleDirections.insert(possibleDirections.begin(), UP_PAIR);
    possibleDirections.insert(possibleDirections.begin(), LEFT_PAIR);
    possibleDirections.remove({currentDirection.first * -1, currentDirection.second * -1});

    QRegion r;
    if (mode == EXIT || mode == RETREAT)
        r = walls;
    else
        r = walls.united(gate);

    QRect t = translated(DOWN_PAIR.first, DOWN_PAIR.second);
    if (r.intersects(t))
        possibleDirections.remove(DOWN_PAIR);

    t = translated(RIGHT_PAIR.first, RIGHT_PAIR.second);
    if (r.intersects(t))
        possibleDirections.remove(RIGHT_PAIR);

    t = translated(UP_PAIR.first, UP_PAIR.second);
    if (r.intersects(t))
        possibleDirections.remove(UP_PAIR);

    t = translated(LEFT_PAIR.first, LEFT_PAIR.second);
    if (r.intersects(t))
        possibleDirections.remove(LEFT_PAIR);
}

bool Ghost::findDirection(std::list<std::pair<short, short>> &possibleDirections, std::pair<short, short> dir) {
    return std::find(possibleDirections.begin(), possibleDirections.end(), dir) != possibleDirections.end();
}

void Ghost::resolveDirectionOverCommonAxisTowards(QPoint target, bool foundDown, bool foundLeft, bool foundRight,
                                                  std::list<std::pair<short, short>> &possibleDirections, bool foundUp) {
    if (foundUp && foundDown) {
        if (target.y() < y())
            possibleDirections.remove(DOWN_PAIR);
        else if (target.y() > y())
            possibleDirections.remove(UP_PAIR);
    }
    if (foundLeft && foundRight) {
        if (target.x() < x())
            possibleDirections.remove(RIGHT_PAIR);
        else if (target.x() > x())
            possibleDirections.remove(LEFT_PAIR);
    }
}

void Ghost::prolongEating() {
    switch (mode) {
        case ATTACK:
        case DEPLOY:
        case RUN:
            if (mode != RUN)
                currentDirection = {currentDirection.first * -1, currentDirection.second * -1};
            mode = RUN;
            internalTimer->start(EAT_TIME);
            break;
        default:
            break;
    }
}

void Ghost::startRetreat() {
    mode = RETREAT;
    speed = 5;
    retreatTarget = exitSquare;
}

QImage Ghost::getSprite() const {
    if (mode == RUN) {
        return sprites.at(RUN);
    }
    else if (mode == RETREAT) {
        return sprites.at(RETREAT);
    }
    else {
        return sprites.at(ATTACK);
    }
}

bool Ghost::canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) {
    QRegion t(translated(currentDirection.first, currentDirection.second));
    if (mode == RETREAT || mode == EXIT) {
        return !t.intersects(walls);
    }
    return !t.intersects(walls.united(gate));
}