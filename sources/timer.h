#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDateTime>

class QTimer;
class Timer:public QObject
{
    Q_OBJECT
    QDateTime dt;
    QTimer *timer;
    int status;
    int secMas[3];
    int numLoop;
public:
    Timer();
private slots:
    void slotTimeUpDate();
public slots:
    void slotTimerStart();
    void slotTimerStop();
signals:
    void sigTimeTick(int,int);
    void sigTimeEnd(int);
};

#endif // TIMER_H
