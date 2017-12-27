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
    explicit MovingSprite(QRect r, const std::string &color);
    virtual ~MovingSprite() = default;
    std::string color;
public:
    void move();
    bool canMaintainCurrentDirection(const QRegion& walls);
    std::pair<short, short> currentDirection = {0, 1};
    std::pair<short, short> nextDirection = {0, 1};
    void setNextDirection(std::pair<short, short> direction);
    virtual void changeDirection(const QRegion& walls) = 0;
};


#endif //TASK8_PACMAN_MOVINGSPRITE_H
