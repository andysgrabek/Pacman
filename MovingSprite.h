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

class MovingSprite: public QRect {

protected:
    explicit MovingSprite(QRect r, int color);
    virtual ~MovingSprite() = default;
    int color;
    std::map<int, QImage> sprites;
    bool shouldMove = false;
public:
    int speed = 1;
    virtual QImage getSprite() const = 0;
    void move();
    bool canBeEaten;
    virtual bool canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) = 0;
    std::pair<short, short> currentDirection = {0, 1};
    std::pair<short, short> nextDirection = {1, 0};
    void setNextDirection(std::pair<short, short> direction);
    virtual void changeDirection(const QRegion &walls, const QRegion &gate) = 0;
};


#endif //TASK8_PACMAN_MOVINGSPRITE_H
