//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_GHOST_H
#define TASK8_PACMAN_GHOST_H

#include "MovingSprite.h"

class Ghost: public MovingSprite {
public:
    explicit Ghost(QRect r, const std::string &color, MovingSprite *pacman);
    void changeDirection(const QRegion& walls) override;
    inline QImage getSprite() const { return sprite; }
private:
    MovingSprite* pacman;
    void calculatePossibleDirections(std::list<std::pair<short, short>> &possibleDirections, const QRegion &walls);
    bool findDirection(std::list<std::pair<short, short>> &possibleDirections, std::pair<short, short> dir);
    void resolveDirectionOverCommonAxis(bool foundUp, bool foundDown, bool foundLeft, bool foundRight,
                                        std::list<std::pair<short, short>>&);
    void resolveDirection(const std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML,
                          QPoint offset);
    QImage sprite;
};


#endif //TASK8_PACMAN_GHOST_H
