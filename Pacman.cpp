//
// Created by andys on 01.12.17.
//

#include "Pacman.h"
#include <cmath>

Pacman::Pacman(QRect r, int color, bool canBeEaten): MovingSprite(r, color) {
    nextDirection = RIGHT_PAIR;
    shouldMove = true;
    this->canBeEaten = canBeEaten;
    loadSprites();
}

void Pacman::changeDirection(const QRegion &walls, const QRegion &gate) {
    if (currentDirection != NONE_PAIR) {
        QRect t = translated(nextDirection.first, nextDirection.second);
        if (walls.united(gate).intersects(t)) {
            return;
        }
        currentDirection = nextDirection;
        nextDirection = NONE_PAIR;
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

bool Pacman::canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) {
    QRegion t(translated(currentDirection.first, currentDirection.second));
    return !t.intersects(walls.united(gate));
}

void Pacman::loadSprites() {
    try {
        sprites[OPEN].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/pacmanOpen.png");
        sprites[CLOSED].load("/Volumes/DATA/OneDrive/IFE Computer Science/Semester 3/OOPC/Task8_Pacman/pacmanClosed.png");
    }
    catch (...) {
        abort();
    }

}
