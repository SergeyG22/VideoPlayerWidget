#ifndef CLOCK_H
#define CLOCK_H
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QLCDNumber>
#include <chrono>
#include <ctime>


class LCDclock: public QWidget{
    QTimer *timer = nullptr;
    QLCDNumber* number = nullptr;
    long long current_time;
public:
    explicit LCDclock (QWidget *parent);
public slots:
     void showTime();
};

class LCDtimer: public QWidget{
    QTimer *timer = nullptr;
    QLCDNumber* number = nullptr;
    short hour = 0;
    short minute = 0;
    short second = 0;
public:
    explicit LCDtimer (QWidget *parent);
public slots:
        void showTimer();
};



















#endif // CLOCK_H
