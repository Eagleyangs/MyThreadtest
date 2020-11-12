#include "MyThread.h"

int MyThread::m_iCount = 0;

MyThread::MyThread()
{

}

void MyThread::run()
{
    qDebug() << "run " << ++m_iCount << " == " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    sleep(5);
    qDebug() << "run " << ++m_iCount << " == " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    emit sigStopTimer();
}
