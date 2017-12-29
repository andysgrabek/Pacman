//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_PACMANBOARD_H
#define TASK8_PACMAN_PACMANBOARD_H

#include <QtGui/QPainter>
#include <QWidget>
#include <vector>
#include <QKeyEvent>
#include <QTimer>
#include <QMainWindow>
#include "Pacman.h"
#include "Ghost.h"

class PacmanBoard: public QMainWindow {

Q_OBJECT

public:
    PacmanBoard(QWidget *parent = nullptr); //NOLINT
    ~PacmanBoard() override;

public slots:
    void moveSprites();
    void changePacmanMouth();

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    std::list<MovingSprite*> createSpritesArray();
    std::list<MovingSprite*> sprites;
    std::list<QRect> smallDots;
    std::list<QRect> bigDots;
    QRegion walls;
    QRegion gate;
    std::vector<Ghost> ghosts;
    void loadGame();
    void addObjects();
    std::vector<std::string> map;
    std::pair<unsigned long, unsigned long> mapSize;
    QTimer *gameTimer;
    QTimer *mouthTimer;
    Pacman pacman;
    bool didHitSmallDot();
    bool didHitBigDot();
    void passThroughBoundary(MovingSprite *sprite);
    void redirectAndMove(MovingSprite *sprite);
    void collectDot();
    void checkVictoryCondition();
};

#endif //TASK8_PACMAN_PACMANBOARD_H
