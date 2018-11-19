#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(680, 720);
    w.setWindowTitle("tetris");
    w.show();

    return a.exec();
}
