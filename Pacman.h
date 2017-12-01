//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_PACMAN_H
#define TASK8_PACMAN_PACMAN_H

#include "MovingSprite.h"

class Pacman: public MovingSprite {

public:
    explicit Pacman(const QColor& color, bool canBeEaten = false): MovingSprite(color, canBeEaten) {}
    void move() override;

};


#endif //TASK8_PACMAN_PACMAN_H
