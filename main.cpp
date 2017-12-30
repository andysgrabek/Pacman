#include <QApplication>
#include "PacmanBoard.h"
#include "Counter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PacmanBoard board;
    LCDDisplay score(&board);
    score.setGeometry(0, BOARD_SIZE_Y, BOARD_SIZE_X, CELL_WIDTH * 3);
    board.setGeometry(0, 0, BOARD_SIZE_X, BOARD_SIZE_Y + CELL_WIDTH * 3);
    board.show();
    return app.exec();
}
