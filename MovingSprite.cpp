//
// Created by andys on 01.12.17.
//

#include <iostream>
#include "MovingSprite.h"

MovingSprite::MovingSprite(QRect r, const int color) : QRect(r) {
    this->color = color;
}

void MovingSprite::setNextDirection(std::pair<short, short> direction) {
    nextDirection = std::move(direction);
}

void MovingSprite::move() {
    if (shouldMove)
        translate(currentDirection.first, currentDirection.second);
}
