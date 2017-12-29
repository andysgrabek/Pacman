//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_MOVINGSPRITE_H
#define TASK8_PACMAN_MOVINGSPRITE_H

#include <QtGui/QColor>
#include <QRect>
#include <vector>
#include <QRegion>
#include <QGraphicsPixmapItem>
#include "pacman_constants.h"

class MovingSprite: public QRect {

protected:
    explicit MovingSprite(QRect r, int color);
    virtual ~MovingSprite() = default;
    int color;
    std::map<int, QImage> sprites;
    bool shouldMove = false;
    virtual void loadSprites() = 0;
public:
    int speed = 2;
    virtual QImage getSprite() const = 0;
    void move();
    bool canBeEaten;
    virtual bool canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) = 0;
    std::pair<short, short> currentDirection = DOWN_PAIR;
    std::pair<short, short> nextDirection = RIGHT_PAIR;
    void setNextDirection(std::pair<short, short> direction);
    virtual void changeDirection(const QRegion &walls, const QRegion &gate) = 0;
};


#endif //TASK8_PACMAN_MOVINGSPRITE_H
