#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QObject>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();

public:
    void run();

signals:
    void sigStopTimer();

private:
    static int m_iCount;
};

#endif // MYTHREAD_H
