//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_GHOST_H
#define TASK8_PACMAN_GHOST_H
#include <QTimer>
#include "MovingSprite.h"

typedef struct FoundDirection {
    bool up, down, left, right;
} FD;

class Ghost: public MovingSprite {

public:
    explicit Ghost(QRect r, int color, MovingSprite *pacman);
    void changeDirection(const QRegion &walls, const QRegion &gate) override;
    int mode;
    void prolongEating();
    void startRetreat();
    QImage getSprite() const override;
    bool canMaintainCurrentDirection(const QRegion &walls, const QRegion &gate) override;
private:
    void deployStrategy(std::list<std::pair<short, short>> &possibleDirections, FD &foundDirections, std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML);
    void runStrategy(std::list<std::pair<short, short>> &possibleDirections);
    void retreatStrategy(std::list<std::pair<short, short>> &possibleDirections, std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML);
    void exitStrategy(std::list<std::pair<short, short>> &possibleDirections, std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML);
    void attackStrategy(std::list<std::pair<short, short>> &possibleDirections, std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML);
    void loadSprites() override;
    QPoint retreatTarget;
    QPoint targetCorner;
    QPoint exitSquare;
    QPoint originalPosition;
    MovingSprite* pacman;
    void calculatePossibleDirections(std::list<std::pair<short, short>> &possibleDirections, const QRegion &walls, const QRegion &gate);
    bool findDirection(std::list<std::pair<short, short>> &possibleDirections, std::pair<short, short> dir);
    void resolveDirectionOverCommonAxisTowards(QPoint target, std::list<std::pair<short, short>> &, FD foundDirection);
    void resolveDirection(const std::vector<std::pair<short, short>> &vector, std::vector<int> &vectorOfML,
                          QPoint offset);
    QTimer *internalTimer;
    void chooseRandomDirection(std::list<std::pair<short, short>> &possibleDirections);
    void restoreInitialDirection();
    void prepareDeployment();
    void findDirections(std::list<std::pair<short, short>> &possibleDirections, FD &foundDirection);
};


#endif //TASK8_PACMAN_GHOST_H
