//
// Created by andys on 01.12.17.
//

#include <QtGui/QPainter>
#include <fstream>
#include "PacmanBoard.h"
#define CELL_WIDTH 25

PacmanBoard::PacmanBoard(QWidget *parent) {
    loadMapFromFile();
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
                QPen pen(Qt::black, 2);
                p.setPen(pen);
                p.fillPath(path, Qt::red);
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

void PacmanBoard::loadMapFromFile() {
    std::ifstream file("/home/andys/CLionProjects/Task8_Pacman/map.txt");
    for (std::string n; file >> n; ) {
        map.push_back(n);
    }

}

void PacmanBoard::paintBoard(QPaintEvent *event) {
    paintEvent(event);
}