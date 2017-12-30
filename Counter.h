#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QLabel>

class LCDDisplay: public QWidget {

Q_OBJECT

public:
    explicit LCDDisplay(QWidget *parent = nullptr);
    QLCDNumber *lcd;
    QLabel *tooltip;
    QLabel *points;
    ~LCDDisplay() override;

public slots:
    void displayInt(int val);
    void displayText(QString text);

signals:
    void valueChanged(int newValue) __unused;
    void textChanged(QString text) __unused;
};

#endif
