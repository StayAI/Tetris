#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    //线程处理函数
    void myTimeOut();
    void setFlag(bool flag = true);

signals:
    void mySignal();

public slots:

private:
    bool isStop;
};

#endif // MYTHREAD_H
