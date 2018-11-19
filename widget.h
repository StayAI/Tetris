#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <mythread.h>
#include "tetris.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void dealSignal();
    void dealClose();
    void keyPressEvent(QKeyEvent *);



signals:
    void startThread();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();

private:
    Ui::Widget *ui;

    int gridW;
    int gridH;
    int startX;
    int startY;


    QThread *thread;
    MyThread *myT;

    Tetris tetris;
    bool startFlag;

};

#endif // WIDGET_H
