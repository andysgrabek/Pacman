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
    explicit Pacman(QRect r, int color, bool canBeEaten = true);
    void changeDirection(const QRegion &walls, const QRegion &gate) override;
    QImage getSprite() const override;
    void switchMouthMode();
    bool canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) override;
private:
    int mouthMode = OPEN;
    void loadSprites() override;
};


#endif //TASK8_PACMAN_PACMAN_H
