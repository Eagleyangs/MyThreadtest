#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "MyThread.h"
#include <QTimer>
#include <QObject>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:

public slots:
    void on_pushButton_clicked();
    void on_pushButton2_clicked();
    void slotTimeOut();
    void slotStopTimer();
    void slotDestroyed();

private:
    Ui::Widget *ui;

    static int m_iNum;
    bool      m_bClick;
    MyThread *m_thread;
    QTimer   *m_timer;
};

#endif // WIDGET_H
