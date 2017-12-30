#include <climits>//
// Created by andys on 01.12.17.
//

#include <fstream>
#include <iostream>
#include "PacmanBoard.h"

PacmanBoard::PacmanBoard(QWidget __unused *parent): pacman(QRect(), YELLOW) {
    gameTimer = new QTimer(this);
    mouthTimer = new QTimer(this);
    loadGame();
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(moveSprites()));
    connect(mouthTimer, SIGNAL(timeout()), this, SLOT(changePacmanMouth()));
    startNewGame();
}

void PacmanBoard::startNewGame() {
    addObjects();
    sprites = createSpritesArray();
    gameTimer->start(DELAY);
    mouthTimer->start(MOUTH_CHANGE_INTERVAL);emit
    textChanged("Arrows to steer, ESC to exit");
}

void PacmanBoard::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    drawWalls(p);
    for (auto& smallDot: smallDots)
        drawDot(p, smallDot, Qt::darkMagenta, 2);
    for (auto& bigDot: bigDots)
        drawDot(p, bigDot, Qt::darkCyan, 3);
    for (auto sprite: sprites)
        p.drawImage(*sprite, sprite->getSprite().scaled(CELL_WIDTH, CELL_WIDTH));
}

void PacmanBoard::drawWalls(QPainter &p) const {
    QPainterPath path;
    path.addRegion(walls);
    QPen pen(Qt::darkBlue, 0);
    p.setPen(pen);
    p.fillPath(path, Qt::darkBlue);
    p.drawPath(path);
    QPen gatePen(Qt::darkGreen, 4);
    p.setPen(gatePen);
    p.drawLine(gate.boundingRect().translated(0, CELL_WIDTH / 4).topLeft(), gate.boundingRect().translated(0, CELL_WIDTH / 4).topRight());
}

void PacmanBoard::drawDot(QPainter &p, const QRect &bigDot, QColor color, int thickness) const {
    QPainterPath path;
    path.addEllipse(bigDot);
    QPen pen(color, thickness);
    p.setPen(pen);
    p.drawPath(path);
}

void PacmanBoard::loadGame() {
    try {
        std::ifstream file("map.txt");
        for (std::string n; file >> n;)
            map.push_back(n);
        file.close();
    }
    catch (...) {
        abort();
    }

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
    clearGame();
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
                    ghosts.emplace_back(QRect(STANDARD_CELL), RED, &pacman);
                    break;
                case 'b':
                    ghosts.emplace_back(QRect(STANDARD_CELL), CYAN, &pacman);
                    break;
                case 'c':
                    ghosts.emplace_back(QRect(STANDARD_CELL), YELLOW, &pacman);
                    break;
                case 'd':
                    ghosts.emplace_back(QRect(STANDARD_CELL), PINK, &pacman);
                    break;
                case 'p':
                    pacman.setRect(STANDARD_CELL);
                    break;
                case 'w':
                    gate = QRect(STANDARD_CELL);
                default:
                    break;
            }
        }
    }
}

void PacmanBoard::clearGame() {
    sprites = std::list<MovingSprite*>();
    smallDots = std::list<QRect>();
    bigDots = std::list<QRect>();
    walls = QRegion();
    gate = QRegion();
    ghosts = std::vector<Ghost>();
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
        case Qt::Key_Return:
            if (!gameTimer->isActive())
                startNewGame();
            break;
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
    if (sprite->x() == size().width() - CELL_WIDTH / 2 && sprite->currentDirection == RIGHT_PAIR)
        sprite->moveLeft(-CELL_WIDTH / 2);
    if (sprite->x() <= -CELL_WIDTH / 2 && sprite->currentDirection == LEFT_PAIR)
        sprite->moveLeft(size().width() - CELL_WIDTH / 2);
}

void PacmanBoard::redirectAndMove(MovingSprite *sprite) {
    for(int i = 0; i < sprite->speed; ++i) {
        if (sprite->nextDirection != NONE_PAIR)
            sprite->changeDirection(walls, gate);
        if (sprite->canMaintainCurrentDirection(walls, gate)) {
            sprite->move();
        }
    }
}

void PacmanBoard::collectDot() {
    if (didHitSmallDot() || didHitBigDot())
        emit scoreIncreased(static_cast<int>(SMALL_DOTS - smallDots.size() + 5 * (BIG_DOTS - bigDots.size())));
}

void PacmanBoard::checkVictoryCondition() {
    if (bigDots.empty() && smallDots.empty()) {
        gameTimer->stop();
        emit textChanged(QString(WIN_TEXT));;
    }
    for (auto& ghost: ghosts) {
        if (ghost.intersects(pacman)) {
            if (pacman.canBeEaten && ghost.mode != RETREAT) {
                gameTimer->stop();
                emit textChanged(QString(LOST_TEXT));
                //exit(3);
            }
            else {
                ghost.startRetreat();
            }
        }
    }
}

void PacmanBoard::changePacmanMouth() {
    pacman.switchMouthMode();
}
