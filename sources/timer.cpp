#include "timer.h"
#include <QTimer>

Timer::Timer()
{
    numLoop=0;
    secMas[0]=5;//1500;
    secMas[1]=5;//300
    secMas[2]=2000;
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimeUpDate()));
}


void Timer::slotTimeUpDate(){
    QDateTime nowTime = QDateTime::currentDateTime();
    int sec = secMas[status]-dt.secsTo(nowTime);
    if(sec>0)emit sigTimeTick(sec,status);
    else {
        numLoop++;
        status = (numLoop<8)?( (status+1)%2):2;
        emit sigTimeEnd(status);
        dt = QDateTime::currentDateTime();
    }
}

void Timer::slotTimerStart(){
    status=0;
    numLoop=0;
    dt = QDateTime::currentDateTime();
    timer ->start();
}

void Timer::slotTimerStop(){
    timer->stop();
}
