#include "timer.h"
#include <QTimer>

Timer::Timer(int time,QObject *parent):QObject(parent)
{
	m_secMas[0]=10;//1500;
	m_secMas[1]=20;//300
	m_secMas[2]=2000;
	m_Rx=0;
	m_pTimer = new QTimer(this);
	m_pTimer->setInterval(1000);
	connect(m_pTimer, SIGNAL(timeout()), SLOT(slotTimeUpDate()));
//	m_pTimer->start();
}


void Timer::slotTimeUpDate(){
    QDateTime nowTime = QDateTime::currentDateTime();
	int sec = m_secMas[((m_Rx&0x70)>>4)-1]-m_dt.secsTo(nowTime);
	if(sec>0)emit sigTimeTick(sec);
    else {
		slotTimerSig(true);
    }
}

void Timer::slotTimerSig(bool sig){
	m_Rx=sig?m_Rx|0x80:m_Rx&0x7f;

	if(!m_Rx){// переход ожидание работа
		m_pTimer->start();
		m_Rx=0x11;
		m_dt = QDateTime::currentDateTime();
		return;
	}

	if((m_Rx&0xb0)==0x10){// переход  работа -> ожидания
		m_pTimer->stop();
		m_Rx=0;
		return;
	}

	if((m_Rx&0xb4)==0x94){ // переход работа отжых
		m_Rx=0x30;
		m_dt = QDateTime::currentDateTime();
		return;
	}

	if((m_Rx&0xb0)==0x90){// переход работа перерыв
		m_Rx=0x20+(m_Rx&0x0f);
		m_dt = QDateTime::currentDateTime();
		return;
	}

	if((m_Rx&0xb0)==0xa0){
		m_pTimer->stop();
		m_Rx=0;
		return;
	}

	if((m_Rx&0xb0)==0x20){
		m_Rx=0x11+(m_Rx&0x0f);
		emit sigCK(false);
		m_dt = QDateTime::currentDateTime();
		return;
	}

	if(m_Rx&0xb0){
		m_pTimer->stop();
		m_Rx=0;
		return;
	}

	if((m_Rx&0xb0)==0x30){
		emit sigCK(true);
		m_Rx+=0x10;
		m_dt = QDateTime::currentDateTime();
		return;
	}
}
