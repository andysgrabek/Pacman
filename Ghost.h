//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_GHOST_H
#define TASK8_PACMAN_GHOST_H

#include "MovingSprite.h"

class Ghost: public MovingSprite {
public:
    explicit Ghost(const QColor& color, void moveStrategy(), bool canBeEaten = false);
    void move() override;
private:
    void (*moveStrategy)();
};


#endif //TASK8_PACMAN_GHOST_H
