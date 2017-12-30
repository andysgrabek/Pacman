#include "Counter.h"
#include "pacman_constants.h"

LCDDisplay::LCDDisplay(QWidget *parent): QWidget(parent) {
    connect(parent, SIGNAL(scoreIncreased(int)), this, SLOT(displayInt(int)));
    connect(parent, SIGNAL(textChanged(QString)), this, SLOT(displayText(QString)));
    lcd = new QLCDNumber(3);
    tooltip = new QLabel();
    tooltip->setText(GAME_TEXT);
    points = new QLabel();
    points->setText("YOUR POINTS:");
    lcd->setSegmentStyle(QLCDNumber::Filled);
    auto *layout = new QHBoxLayout;
    layout->addWidget(tooltip);
    layout->addWidget(points);
    layout->addWidget(lcd);
    setLayout(layout);
}

void LCDDisplay::displayInt(int val) {
    lcd->display(val);
}

void LCDDisplay::displayText(QString text) {
    tooltip->setText(text);
}

LCDDisplay::~LCDDisplay() {
    delete lcd;
    delete tooltip;
    delete points;
}


