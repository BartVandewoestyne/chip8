#include "Screen.h"

#include <QPainter>

void Screen::paintEvent(QPaintEvent*)
{
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.setPen(QPen(Qt::black, 12));
     painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
     painter.drawRect(80, 80, 400, 240);
}
