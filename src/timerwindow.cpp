#include <QLabel>
#include <QSystemTrayIcon>
#include <QVBoxLayout>

#include "timerwindow.h"
#include "staticview.h"
#include "trayicon.h"
#include "setting.h"
#include "timer.h"

#include <QApplication>

TimerWindow::TimerWindow(QWidget *parent) :QDialog(parent){

		Setting *mSetting=Setting::Instance();

		QFont font;
		font.fromString( mSetting->value("font"));

		QVBoxLayout *vbox = new QVBoxLayout(this);
		m_plblDisp = new QLabel("not init timer",this);
		m_plblDisp->setFont(font);
		vbox->addWidget(m_plblDisp);
//		this->setCentralWidget(m_plblDisp);
		setWindowIcon(QIcon(":image/icon.png"));
		setWindowTitle("Pomidorka");
		setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint| Qt::Tool);//! @todo делать через флаги раб стола
		setAttribute(Qt::WA_TranslucentBackground);
		setEnabled(false);

		QPalette pal = palette();
			pal.setColor( QPalette::Window, Qt::transparent );
			pal.setColor( QPalette::Button, Qt::transparent );
			pal.setColor( QPalette::Base, Qt::transparent );
			pal.setColor( QPalette::Light, Qt::transparent );
			pal.setColor( QPalette::Midlight, Qt::transparent );
			pal.setColor( QPalette::Dark, Qt::transparent );
			pal.setColor( QPalette::Mid, Qt::transparent );
			pal.setColor( QPalette::Shadow, Qt::transparent );


		setPalette(pal);

		QString pos=mSetting->value("pos");
		this->move(pos.left(pos.indexOf(":")).toInt(),pos.right(pos.size()-pos.indexOf(":")-1).toInt());

		TrayIcon *trayicon = new TrayIcon(this);
		connect(trayicon,SIGNAL(sigExit()),this,SLOT(close()));

		m_pTimer = new Timer(300,this);
		connect(m_pTimer,SIGNAL(sigTimeTick(int)),this,SLOT(slotTimeTick(int)));
		connect(trayicon,SIGNAL(sigTimerSignal(bool)),m_pTimer,SLOT(slotTimerSig(bool)));
}

TimerWindow::~TimerWindow(){
	Setting::Instance()->~Setting();
}

void TimerWindow::slotTimeTick(int iTimeLast){
	int last=iTimeLast;
	int hh=last/60;
	int mm=last%60;
	QString str = QString::number(hh)+":"+QString::number(mm);
	m_plblDisp->setText(str);
	}

void TimerWindow::slotShowStat(){
	StaticView *StaticWindows = new StaticView(this);
	StaticWindows->show();
}
