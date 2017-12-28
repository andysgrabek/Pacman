//
// Created by andys on 01.12.17.
//

#include <iostream>
#include "MovingSprite.h"

MovingSprite::MovingSprite(QRect r, const std::string &color) : QRect(r) {
    this->color = color;
}

bool MovingSprite::canMaintainCurrentDirection(const QRegion& walls) {
    QRegion t(translated(currentDirection.first, currentDirection.second));
    return !t.intersects(walls);
}

void MovingSprite::setNextDirection(std::pair<short, short> direction) {
    nextDirection = std::move(direction);
}

void MovingSprite::move() {
    translate(currentDirection.first * speed.first, currentDirection.second * speed.second);
}
