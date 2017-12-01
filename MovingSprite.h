//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_MOVINGSPRITE_H
#define TASK8_PACMAN_MOVINGSPRITE_H


#include <QtGui/QColor>

class MovingSprite {

protected:
    explicit MovingSprite(QColor color, bool canBeEaten = false);
    virtual ~MovingSprite() = default;
    QColor color;
    std::pair<unsigned long, unsigned long> startingCell = {0, 0};

public:
    bool canBeEaten;
    virtual void move() = 0;
};


#endif //TASK8_PACMAN_MOVINGSPRITE_H
