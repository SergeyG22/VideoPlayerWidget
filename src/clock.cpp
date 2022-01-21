#include "clock.h"


LCDclock::LCDclock (QWidget *parent): QWidget(parent){
    this->resize(220,70);
    number = new QLCDNumber(this);
    number->setSegmentStyle(QLCDNumber::Flat);
    number->setMinimumSize(220,70);
    number->setDigitCount(8);
    number->setStyleSheet("background-color: rgb(10, 241, 244); border: 2px solid rgb(113, 113, 113);border-width: 2px;border-radius: 10px;color: rgb(0, 0, 0);");
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &LCDclock::showTime);
    timer->start(10);
    this->setStyleSheet("background-color: rgba(252, 255, 255, 0%);");
}

LCDtimer::LCDtimer (QWidget *parent): QWidget(parent){
    this->resize(220,70);
    number = new QLCDNumber(this);
    number->setSegmentStyle(QLCDNumber::Flat);
    number->setMinimumSize(220,70);
    number->setDigitCount(8);
    number->setStyleSheet("background-color: rgb(10, 241, 244); border: 2px solid rgb(113, 113, 113);border-width: 2px;border-radius: 10px;color: rgb(0, 0, 0);");
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &LCDtimer::showTimer);
    timer->start(1000);
    this->setStyleSheet("background-color: rgba(252, 255, 255, 0%);");
}


void LCDclock::showTime(){
        auto now = std::chrono::system_clock::now();
        current_time = std::chrono::system_clock::to_time_t(now);
        QString time = QString::number(localtime(&current_time)->tm_hour) + ":"
                     + QString::number(localtime(&current_time)->tm_min) + ":"
                     + QString::number(localtime(&current_time)->tm_sec);
        number->display(time);
}

void LCDtimer::showTimer(){
    second++;
    if(second == 60){ second = 0;minute +=1; }
    if(minute == 60){ hour += 1;}
    if(hour == 24)  { hour = 0;}
    QString time = QString::number(hour) + ":"
                 + QString::number(minute) + ":"
                 + QString::number(second);
    number->display(time);
}

