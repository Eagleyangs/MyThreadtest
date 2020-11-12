#include "Widget.h"
#include "ui_Widget.h"

int Widget::m_iNum = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_bClick = false;

    m_thread = new MyThread();
    m_timer = new QTimer();

    connect(m_timer, &QTimer::timeout, this, &Widget::slotTimeOut);
    connect(m_thread, &MyThread::sigStopTimer, this, &Widget::slotStopTimer);
    connect(this, &Widget::destroyed, this, &Widget::slotDestroyed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    m_bClick = true;
    qDebug() << "m_timer->isActive : " << m_timer->isActive();
    if(m_timer->isActive() == false)
    {
        qDebug() << "m_timer->start";
        m_timer->start(100);
    }
    qDebug() << "m_thread->isRunning : " << m_thread->isRunning();

    if(!m_thread->isRunning())
        m_thread->start();
    qDebug() << "on_pushButton_clicked : " << m_iNum << "   m_bClick: " << m_bClick;
}

void Widget::on_pushButton2_clicked()
{
    m_bClick = false;
    qDebug() << "m_timer->isActive : " << m_timer->isActive();
    if(m_timer->isActive())
    {
        qDebug() << "slotStopTimer";
        slotStopTimer();
    }

    qDebug() << "on_pushButton2_clicked : " << m_iNum << "   m_bClick: " << m_bClick;
}

void Widget::slotTimeOut()
{
    qDebug() << "slotTimeOut : " << m_iNum;
    m_iNum++;
    ui->lcdNumber->display(m_iNum);
}

void Widget::slotStopTimer()
{
    qDebug() << "slotStopTimer : " << m_iNum;
    m_timer->stop();
}

void Widget::slotDestroyed()
{
    qDebug() << "slotDestroyed : " << m_iNum;
    m_thread->wait();
    qDebug() << "wait : " << m_iNum;
    m_thread->quit();
    qDebug() << "quit : " << m_iNum;
}
