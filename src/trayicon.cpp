#include <QSystemTrayIcon>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QApplication>


#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent) :QObject(parent){
	QSystemTrayIcon *trayicon = new QSystemTrayIcon(this);
		trayicon->setToolTip ("Pomidorka");
		trayicon->setIcon(QIcon(":image/tomatoicon.ico"));
		trayicon->show();
		trayicon->setContextMenu(createMenu());

//	connect(trayicon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, //(act, SIGNAL(triggered()), this->parent(), SLOT(slotHideShow()));
}

QMenu * TrayIcon::createMenu(){
	QMenu *menu = new QMenu();
//		menuOptions->setTitle(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));

	{
		QAction *act = new QAction(tr("Start/Stop"), this);
		menu->addAction(act);
		connect(act, SIGNAL(triggered()), this, SLOT(slotTimerSignal()));
	}
	{
		QAction *act = new QAction(tr("Statistics"), this);
		act->setStatusTip(tr("Statistics"));
		menu->addAction(act);
		connect(act, SIGNAL(triggered()), this->parent(), SLOT(slotShowStat()));
	}
	{
		QAction *act = new QAction(tr("Setting"), this);
		menu->addAction(act);
//		connect(act, SIGNAL(triggered()), this->parent(), SLOT(slotHideShowTimer()));
	}
	menu->addSeparator();
	{
		m_pactExit = new QAction(tr("E&xit"), this);
		m_pactExit->setShortcuts(QKeySequence::Quit);
		m_pactExit->setStatusTip(tr("Exit the application"));
		menu->addAction(m_pactExit);
		connect(m_pactExit, SIGNAL(triggered()), this, SLOT(slotExit()));

	}

	return menu;
}

void TrayIcon::slotExit(){
	emit sigExit();
	QApplication::exit(0);
}

void TrayIcon::slotTimerSignal(){
	emit sigTimerSignal(false);
}


