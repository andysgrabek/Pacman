#include <iostream>
#include <vector>
#include <string>
#include <QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>

using namespace std;

int main(int argc, char ** argv) {
    QApplication qapp (argc, argv);
    QFont font("Fira Code");
    font.setPixelSize(18);
    QPushButton button("Hello world !");
    button.show();
    return qapp.exec();

}