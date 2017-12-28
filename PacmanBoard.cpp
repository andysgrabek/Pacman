//
// Created by andys on 01.12.17.
//

#include <fstream>
#include <iostream>
#include "PacmanBoard.h"

#define LEFT_PAIR std::pair<short, short>(-1, 0)
#define RIGHT_PAIR std::pair<short, short>(1, 0)
#define UP_PAIR std::pair<short, short>(0, -1)
#define DOWN_PAIR std::pair<short, short>(0, 1)
#define NONE_PAIR std::pair<short, short>(0, 0)
#define FPS 60
#define DELAY (1000 / FPS)
#define MOUTH_CHANGE_INTERVAL 200
#define CELL_WIDTH 25
#define STANDARD_CELL column * CELL_WIDTH, row * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH
#define SMALL_DOT_CELL column * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_WIDTH + CELL_WIDTH / 2, CELL_WIDTH / 8, CELL_WIDTH / 8
#define BIG_DOT_CELL column * CELL_WIDTH + CELL_WIDTH / 2 - CELL_WIDTH / 16, row * CELL_WIDTH + CELL_WIDTH / 2 - CELL_WIDTH / 16, CELL_WIDTH / 4, CELL_WIDTH / 4

PacmanBoard::PacmanBoard(QWidget *parent): pacman(QRect(), "yellow") {
    gameTimer = new QTimer(this);
    mouthTimer = new QTimer(this);
    loadGame();
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(moveSprites()));
    connect(mouthTimer, SIGNAL(timeout()), this, SLOT(changePacmanMouth()));
    addObjects();
    sprites = createSpritesArray();
    gameTimer->start(DELAY);
    mouthTimer->start(MOUTH_CHANGE_INTERVAL);
}

void PacmanBoard::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRegion(walls);
    QPen pen(Qt::darkBlue, 0);
    p.setPen(pen);
    p.fillPath(path, Qt::darkBlue);
    p.drawPath(path);

    for (auto& smallDot: smallDots) {
        QPainterPath path;
        path.addEllipse(smallDot);
        QPen pen(Qt::darkMagenta, 2);
        p.setPen(pen);
        p.drawPath(path);
    }

    for (auto& bigDot: bigDots) {
        QPainterPath path;
        path.addEllipse(bigDot);
        QPen pen(Qt::darkCyan, 3);
        p.setPen(pen);
        p.drawPath(path);
    }

    for (auto sprite: sprites) {
        p.drawImage(*sprite, sprite->getSprite().scaled(CELL_WIDTH, CELL_WIDTH));
    }

}

void PacmanBoard::loadGame() {
    std::ifstream file("map.txt");
    for (std::string n; file >> n;)
        map.push_back(n);
    file.close();
}

void PacmanBoard::moveSprites() {
    for (MovingSprite* sprite: sprites) {
        redirectAndMove(sprite);
        passThroughBoundary(sprite);
    }
    collectDot();
    checkVictoryCondition();
    update();
}

void PacmanBoard::addObjects() {
    for (unsigned int column = 0; column < map.at(0).size(); ++column) {
        for (unsigned int row = 0; row < map.size(); ++row) {
            switch (map[row][column]) {
                case '0':
                    walls = walls.united(QRect(STANDARD_CELL));
                    break;
                case '1':
                    smallDots.emplace_back(SMALL_DOT_CELL);
                    break;
                case '2':
                    bigDots.emplace_back(BIG_DOT_CELL);
                    break;
                case 'a':
                    ghosts.emplace_back(QRect(STANDARD_CELL), "red", &pacman);
                    break;
                case 'b':
                    ghosts.emplace_back(QRect(STANDARD_CELL), "cyan", &pacman);
                    break;
                case 'c':
                    ghosts.emplace_back(QRect(STANDARD_CELL), "yellow", &pacman);
                    break;
                case 'd':
                    ghosts.emplace_back(QRect(STANDARD_CELL), "pink", &pacman);
                    break;
                case 'p':
                    pacman.setRect(STANDARD_CELL);
                    break;
                default:
                    break;
            }
        }
    }
}

void PacmanBoard::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Down:
            pacman.setNextDirection(DOWN_PAIR);
            break;
        case Qt::Key_Up:
            pacman.setNextDirection(UP_PAIR);
            break;
        case Qt::Key_Left:
            pacman.setNextDirection(LEFT_PAIR);
            break;
        case Qt::Key_Right:
            pacman.setNextDirection(RIGHT_PAIR);
            break;
        case Qt::Key_Escape:
            exit(1);
        default:
            break;
    }
}

bool PacmanBoard::didHitBigDot() {
    QRect t = pacman.translated(pacman.currentDirection.first, pacman.currentDirection.second);
    for (QRect& bigDot: bigDots) {
        if (t.intersects(bigDot)) {
            bigDots.remove(bigDot);
            if (pacman.canBeEaten) {
                pacman.canBeEaten = false;
            }
            for (auto& ghost: ghosts) {
                ghost.prolongEating();
            }
            return true;
        }
    }
    return false;
}

bool PacmanBoard::didHitSmallDot() {
    QRect t = pacman.translated(pacman.currentDirection.first, pacman.currentDirection.second);
    for (QRect& smallDot: smallDots) {
        if (t.intersects(smallDot)) {
            smallDots.remove(smallDot);
            return true;
        }
    }
    return false;
}

PacmanBoard::~PacmanBoard() {
    delete mouthTimer;
    delete gameTimer;
}

std::list<MovingSprite *> PacmanBoard::createSpritesArray() {
    std::list<MovingSprite*> sprites;
    sprites.emplace_back(&pacman);
    for (Ghost &ghost: ghosts) {
        sprites.emplace_back(&ghost);
    }
    return sprites;
}

void PacmanBoard::passThroughBoundary(MovingSprite *sprite) {
    if (sprite->x() >= size().width() && sprite->currentDirection == RIGHT_PAIR)
        sprite->moveLeft(0);

    if (sprite->x() <= -CELL_WIDTH && sprite->currentDirection == LEFT_PAIR)
        sprite->moveLeft(size().width() + CELL_WIDTH);
}

void PacmanBoard::redirectAndMove(MovingSprite *sprite) {
    if (sprite->nextDirection != NONE_PAIR)
        sprite->changeDirection(walls);
    if (sprite->canMaintainCurrentDirection(walls)) {
        sprite->move();
    }
}

void PacmanBoard::collectDot() {
    if (didHitSmallDot()) {
        std::clog << "Small dots: " << smallDots.size() << '\n';
    }
    else if (didHitBigDot()) {
        std::clog << "Big dots: " << bigDots.size() << '\n';
    }
}

void PacmanBoard::checkVictoryCondition() {
    if (bigDots.empty() && smallDots.empty()) {
        exit(2);
    }
    for (auto& ghost: ghosts) {
        if (ghost.intersects(pacman)) {
            if (pacman.canBeEaten)
                exit(3);
            else
                ghost.startRetreat();
        }
    }
}

void PacmanBoard::changePacmanMouth() {
    pacman.switchMouthMode();
}
