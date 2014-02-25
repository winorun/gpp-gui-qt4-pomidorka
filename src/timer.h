#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDateTime>

class QTimer;
class Timer:public QObject
{
    Q_OBJECT
	QDateTime m_dt;
	QTimer *m_pTimer;
	int m_secMas[3];
	unsigned char m_Rx;
	unsigned char m_S0;
public:
	Timer(int time, QObject *parent = 0);
private slots:
    void slotTimeUpDate();
public slots:
	void slotTimerSig(bool);
signals:
	void sigTimeTick(int);
	void sigCK(bool big=false);
};

#endif // TIMER_H
