//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_GHOST_H
#define TASK8_PACMAN_GHOST_H
#include <QTimer>
#include "MovingSprite.h"

class Ghost: public MovingSprite {

public:
    explicit Ghost(QRect r, const std::string &color, MovingSprite *pacman);
    void changeDirection(const QRegion& walls) override;
    int mode;
    void prolongEating();
    void startRetreat();
    QImage getSprite() const override;
private:
    QPoint targetCorner;
    QPoint exitSquare;
    QPoint originalPosition;
    MovingSprite* pacman;
    void calculatePossibleDirections(std::list<std::pair<short, short>> &possibleDirections, const QRegion &walls);
    bool findDirection(std::list<std::pair<short, short>> &possibleDirections, std::pair<short, short> dir);
    void resolveDirectionOverCommonAxisTowards(QPoint target, bool foundDown, bool foundLeft, bool foundRight,
                                               std::list<std::pair<short, short>> &, bool foundUp);
    void resolveDirection(const std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML,
                          QPoint offset);
    QTimer *internalTimer;
    void chooseRandomDirection(std::list<std::pair<short, short>> &possibleDirections);
    void restoreInitialDirection();
};


#endif //TASK8_PACMAN_GHOST_H
