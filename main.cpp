#include <QApplication>
#include "PacmanBoard.h"
#include "pacman_constants.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PacmanBoard board;
    board.setGeometry(0, 0, BOARD_SIZE_X, BOARD_SIZE_Y);
    board.show();
    return app.exec();
}
