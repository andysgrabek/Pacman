//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_PACMAN_H
#define TASK8_PACMAN_PACMAN_H

#include "MovingSprite.h"

class Pacman: public MovingSprite {
public:
    bool canBeEaten;
    explicit Pacman(QRect r, const std::string& color, bool canBeEaten = true);
    void changeDirection(const QRegion& walls) override;
};


#endif //TASK8_PACMAN_PACMAN_H
