//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_PACMAN_H
#define TASK8_PACMAN_PACMAN_H

#include "MovingSprite.h"

enum MOUTH_MODE {
    OPEN, CLOSED
};

class Pacman: public MovingSprite {
public:
    explicit Pacman(QRect r, const std::string& color, bool canBeEaten = true);
    void changeDirection(const QRegion& walls) override;
    QImage getSprite() const override;
    void switchMouthMode();
private:
    int mouthMode = OPEN;
};


#endif //TASK8_PACMAN_PACMAN_H
