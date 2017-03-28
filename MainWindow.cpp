#include "MainWindow.h"

#include "Screen.h"

#include <QPainter>

MainWindow::MainWindow()
{
    auto widget = new Screen();
    
    QPainter painter(widget);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotDotLine, Qt::RoundCap));
    painter.drawEllipse(80, 80, 400, 240);

    setCentralWidget(widget);
}
