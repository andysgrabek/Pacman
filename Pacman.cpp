//
// Created by andys on 01.12.17.
//

#include "Pacman.h"
#include <cmath>
#define LEFT_PAIR std::pair<short, short>(-1, 0)
#define RIGHT_PAIR std::pair<short, short>(1, 0)
#define UP_PAIR std::pair<short, short>(0, -1)
#define DOWN_PAIR std::pair<short, short>(0, 1)

Pacman::Pacman(QRect r, const std::string& color, bool canBeEaten): MovingSprite(r, color) {
    nextDirection = RIGHT_PAIR;
    speed = {1, 1};
    this->canBeEaten = canBeEaten;
    sprites[OPEN].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/pacmanOpen.png");
    sprites[CLOSED].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/pacmanClosed.png");
}

void Pacman::changeDirection(const QRegion& walls) {
    if (currentDirection != std::pair<short, short>(0, 0)) {
        QRect t = translated(nextDirection.first, nextDirection.second);
        if (walls.intersects(t)) {
            return;
        }
        currentDirection = nextDirection;
        nextDirection = {0, 0};
    }
}

QImage Pacman::getSprite() const {
    QTransform rotation;
    if (currentDirection == UP_PAIR) {
        rotation.rotateRadians(-M_PI_2);
    }
    else if (currentDirection == DOWN_PAIR) {
        rotation.rotateRadians(M_PI_2);
    }
    else if (currentDirection == LEFT_PAIR) {
        rotation.rotateRadians(M_PI);
    }
    else {
        rotation.rotateRadians(0);
    }
    return sprites.at(mouthMode).transformed(rotation);
}

void Pacman::switchMouthMode() {
    if (mouthMode == OPEN) {
        mouthMode = CLOSED;
    }
    else {
        mouthMode = OPEN;
    }
}
