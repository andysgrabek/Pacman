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
    explicit PacmanBoard(QWidget  __unused *parent = nullptr);
    ~PacmanBoard() override;

public slots:
    void moveSprites();
    void changePacmanMouth();

signals:
    void scoreIncreased(int value) __unused;
    void textChanged(QString text) __unused;

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
    Pacman pacman;
    std::vector<std::string> map;
    QTimer *gameTimer;
    QTimer *mouthTimer;
    void loadGame();
    void addObjects();
    bool didHitSmallDot();
    bool didHitBigDot();
    void passThroughBoundary(MovingSprite *sprite);
    void redirectAndMove(MovingSprite *sprite);
    void collectDot();
    void checkVictoryCondition();
    void drawDot(QPainter &p, const QRect &bigDot, QColor color, int thickness) const;
    void drawWalls(QPainter &p) const;

    void clearGame();

    void startNewGame();
};

#endif //TASK8_PACMAN_PACMANBOARD_H
