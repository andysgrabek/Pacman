//
// Created by andys on 01.12.17.
//

#include "Pacman.h"

Pacman::Pacman(QRect r, const std::string& color, bool canBeEaten): MovingSprite(r, color), canBeEaten(canBeEaten) {
    nextDirection = {1, 0};
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
