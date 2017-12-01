//
// Created by andys on 01.12.17.
//

#include <QtGui/QPainter>
#include <fstream>
#include "PacmanBoard.h"
#include "Pacman.h"
#include "Ghost.h"

#define CELL_WIDTH 25
#define NUMBER_OF_GHOSTS 4
#define GHOST_NAMES {"Blinky", "Pinky", "Inky", "Clyde"}
#define GHOST_COLORS {Qt::red, Qt::blue, Qt::cyan, Qt::darkYellow}

void nullStrategy() {}

PacmanBoard::PacmanBoard(QWidget *parent) {
    std::vector<std::string> ghostNames = GHOST_NAMES;
    std::vector<QColor> ghostColors = GHOST_COLORS;
    sprites["Pacman"] = new Pacman(Qt::yellow, true);
    for (unsigned short ghost = 0; ghost < NUMBER_OF_GHOSTS; ++ghost) {
        sprites[ghostNames[ghost]] = new Ghost(ghostColors[ghost], nullStrategy);
    }
    loadGame();
}

void PacmanBoard::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    for(unsigned int column = 0; column < map.at(0).size(); ++column) {
        for (unsigned int row = 0; row < map.size(); ++row) {
            if (map[row][column] == '0') {
                QPainterPath path;
                path.addRect(QRectF(column * CELL_WIDTH, row * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH));
                QPen pen(Qt::darkBlue, 2);
                p.setPen(pen);
                p.fillPath(path, Qt::darkBlue);
                p.drawPath(path);
            }
            else if (map[row][column] == '1') {
                QPainterPath path;
                path.addEllipse(
                        QPointF(column * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_WIDTH + CELL_WIDTH / 2),
                        CELL_WIDTH / 8,
                        CELL_WIDTH / 8);
                QPen pen(Qt::darkMagenta, 2);
                p.setPen(pen);
                p.drawPath(path);
            }
            else if (map[row][column] == '2') {
                QPainterPath path;
                path.addEllipse(
                        QPointF(column * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_WIDTH + CELL_WIDTH / 2),
                        CELL_WIDTH / 4,
                        CELL_WIDTH / 4);
                QPen pen(Qt::darkCyan, 3);
                p.setPen(pen);
                p.drawPath(path);
            }
        }
    }
}

void PacmanBoard::loadGame() {
    std::ifstream file("/home/andys/CLionProjects/Task8_Pacman/map.txt");
    for (std::string n; file >> n; ) {
        map.push_back(n);
    }
}

void PacmanBoard::paintBoard(QPaintEvent *event) {
    paintEvent(event);
}

bool PacmanBoard::isBoundaryWall(std::pair<unsigned long, unsigned long> cell) {
    return false;
}
