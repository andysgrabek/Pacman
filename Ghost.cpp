//
// Created by andys on 01.12.17.
//

#include "Ghost.h"

Ghost::Ghost(const QColor& color, void (*moveStrategy)(), bool canBeEaten): MovingSprite(color, canBeEaten) {
    this->moveStrategy = moveStrategy;
}

void Ghost::move() {

}
