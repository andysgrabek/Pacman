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

Ghost::Ghost(QRect r, const std::string &color, MovingSprite *pacman) : MovingSprite(r, color) {
    this->pacman = pacman;
    QString path("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/");
    path.append(color.c_str());
    std::cout << path.toStdString();
    sprite.load(path);

}

void Ghost::changeDirection(const QRegion& walls) {

    std::list<std::pair<short, short>> possibleDirections;
    calculatePossibleDirections(possibleDirections, walls);

    if (color == "red" || color == "yellow" || color == "pink") {

        bool foundUp = findDirection(possibleDirections, UP_PAIR);
        bool foundDown = findDirection(possibleDirections, DOWN_PAIR);
        bool foundLeft = findDirection(possibleDirections, LEFT_PAIR);
        bool foundRight = findDirection(possibleDirections, RIGHT_PAIR);

        resolveDirectionOverCommonAxis(foundUp, foundDown, foundLeft, foundRight, possibleDirections);

        std::vector<std::pair<short, short>> vector {std::begin(possibleDirections), std::end(possibleDirections)};

        std::vector<int> vectorOfML;

        vectorOfML.reserve(vector.size());

        int isWithinPinkOffset = (topLeft() - pacman->topLeft()).manhattanLength() <= PINK_OFFSET;

        if (color == "red" || (color == "pink" && isWithinPinkOffset)) {
            resolveDirection(vector, vectorOfML, pacman->topLeft());
        }
        else if (color == "pink") {
            resolveDirection(vector, vectorOfML, {CELL_WIDTH, CELL_WIDTH});
        }
        else if (color == "yellow") {
            resolveDirection(vector, vectorOfML, QPoint(pacman->currentDirection.first * GRAY_OFFSET, pacman->currentDirection.second * GRAY_OFFSET));
        }
    }

    else if (color == "cyan") {
        std::vector<std::pair<short, short>> vector {std::begin(possibleDirections), std::end(possibleDirections)};
        std::shuffle(vector.begin(), vector.end(), std::mt19937(std::random_device()()));
        nextDirection = vector[0];
    }


    if (currentDirection != std::pair<short, short>(0, 0)) {
        QRect d = translated(nextDirection.first, nextDirection.second);
        if (walls.intersects(d)) {
            return;
        }
        currentDirection = nextDirection;
    }
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

void Ghost::calculatePossibleDirections(std::list<std::pair<short, short>> &possibleDirections, const QRegion &walls) {
    possibleDirections.insert(possibleDirections.begin(), DOWN_PAIR);
    possibleDirections.insert(possibleDirections.begin(), RIGHT_PAIR);
    possibleDirections.insert(possibleDirections.begin(), UP_PAIR);
    possibleDirections.insert(possibleDirections.begin(), LEFT_PAIR);
    possibleDirections.remove({currentDirection.first * -1, currentDirection.second * -1});

    QRect t = translated(DOWN_PAIR.first, DOWN_PAIR.second);
    if (walls.intersects(t))
        possibleDirections.remove(DOWN_PAIR);

    t = translated(RIGHT_PAIR.first, RIGHT_PAIR.second);
    if (walls.intersects(t))
        possibleDirections.remove(RIGHT_PAIR);

    t = translated(UP_PAIR.first, UP_PAIR.second);
    if (walls.intersects(t))
        possibleDirections.remove(UP_PAIR);

    t = translated(LEFT_PAIR.first, LEFT_PAIR.second);
    if (walls.intersects(t))
        possibleDirections.remove(LEFT_PAIR);
}

bool Ghost::findDirection(std::list<std::pair<short, short>> &possibleDirections, std::pair<short, short> dir) {
    return std::find(possibleDirections.begin(), possibleDirections.end(), dir) != possibleDirections.end();
}

void Ghost::resolveDirectionOverCommonAxis(bool foundUp, bool foundDown, bool foundLeft, bool foundRight,
                                           std::list<std::pair<short, short>>& possibleDirections) {
    if (foundUp && foundDown) {
        if (pacman->y() < y())
            possibleDirections.remove(DOWN_PAIR);
        else if (pacman->y() > y())
            possibleDirections.remove(UP_PAIR);
    }
    if (foundLeft && foundRight) {
        if (pacman->x() < x())
            possibleDirections.remove(RIGHT_PAIR);
        else if (pacman->x() > x())
            possibleDirections.remove(LEFT_PAIR);
    }
}

