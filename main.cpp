#include <QApplication>
#include "PacmanBoard.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PacmanBoard board;
    board.setGeometry(100, 100, 700, 725);
    board.show();
    return app.exec();
}
