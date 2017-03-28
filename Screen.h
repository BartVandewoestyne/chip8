#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

class QPaintEvent;

class Screen : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent* event);
};

#endif  // SCREEN_H
