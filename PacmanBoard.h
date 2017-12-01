//
// Created by andys on 01.12.17.
//

#ifndef TASK8_PACMAN_PACMANBOARD_H
#define TASK8_PACMAN_PACMANBOARD_H

#include <QWidget>
#include <vector>
#include "MovingSprite.h"

class PacmanBoard: public QWidget {

Q_OBJECT

public:
    PacmanBoard(QWidget *parent = nullptr); //NOLINT

public slots:
    void paintBoard(QPaintEvent *event = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void loadGame();
    bool isBoundaryWall(std::pair<unsigned long, unsigned long> cell);
    std::vector<std::string> map;
    std::pair<unsigned long, unsigned long> mapSize;
    std::map<std::string, MovingSprite*> sprites;
};

#endif //TASK8_PACMAN_PACMANBOARD_H
