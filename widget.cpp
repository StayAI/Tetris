#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //动态分配空间,不能指定父对象
    myT = new MyThread();

    //创建子线程
    thread = new QThread();

    //把自定义线程加入到子线程中
    myT->moveToThread(thread);

    connect(myT, &MyThread::mySignal, this, &Widget::dealSignal);
    connect(this, &Widget::startThread, myT, &MyThread::myTimeOut);
    connect(this, &Widget::destroyed, this, &Widget::dealClose);

    startFlag = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealClose()
{
    on_buttonStop_clicked();
    delete myT;
}

void Widget::dealSignal()
{
    tetris.Deal_Key();//按键处理
    tetris.Tetris_Move();//方块向下移动一步
    tetris.Line_Full();//判断一行是否满
    tetris.setKey(0);

    if (tetris.GameOver())//游戏结束自动按下停止按键
        on_buttonStop_clicked();

    ui->lcdNumber->display( tetris.getScore() );//显示分数
    update();//刷新
}


void Widget::paintEvent(QPaintEvent *)
{
    gridW = tetris.getSize();
    gridH = tetris.getSize();

    startX = gridW;
    startY = gridH;

    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);

    for (int i=0; i<17; i++)
    {
        p.drawLine(startX, startY+i*gridH, startX+10*gridW, startY+i*gridH);
    }
    for (int i=0; i<11; i++)
    {
        p.drawLine(startX+i*gridW, startY, startX+i*gridW, startY+16*gridH);
    }

    //创建画刷对象
    QBrush brush;
    brush.setColor( Qt::red );//设置颜色
    brush.setStyle( Qt::Dense4Pattern);//设置样式

    p.setBrush(brush);

    //绘制下一个俄罗斯方块
    if (startFlag == 1)
    {
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                if (gra[tetris.getIndexNext()][i][j] == 1)//获取下一个俄罗斯方块的索引值，绘制下一个俄罗斯方块，数组内如果是1，就代表有方块
                {
                    p.drawRect( (j+12)*tetris.getSize(), (i+3)*tetris.getSize(), tetris.getSize(), tetris.getSize());
                }
                mapTemp[i][j] = maps[i][j];
            }
        }
    }

    for (int i=3; i<=18; i++)//数组内如果是1，就代表有方块，然后画圆
    {
        for (int j=1; j<=10; j++)
        {
            if (mapTemp[i][j] == 1)
            {
                p.drawRect(j*tetris.getSize(), (i-2)*tetris.getSize(), tetris.getSize(), tetris.getSize());
            }
            mapTemp[i][j] = maps[i][j];
        }
    }
}


void Widget::on_buttonStart_clicked()
{
    if (thread->isRunning() == true)
        return ;

    startFlag = 1;

    //启动线程，但是没有启动线程处理函数
    thread->start();
    myT->setFlag(false);

    //不能直接调用线程处理函数
    //直接调用，导致线程处理函数和主线程在同一个线程
    //myT->myTimeout();

    //只能通过signal-slot方式调用
    emit startThread();

}

void Widget::on_buttonStop_clicked()
{
    if (thread->isRunning() == false)
        return ;

    myT->setFlag(true);
    thread->quit();//手头工作while1 处理不完，从while1下手
    thread->wait();
}


void Widget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
    {
        tetris.setKey(1);
    }
    if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
    {
        tetris.setKey(2);
    }
    if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
    {
        tetris.setKey(3);
    }
    if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
    {
        tetris.setKey(4);
    }
}
