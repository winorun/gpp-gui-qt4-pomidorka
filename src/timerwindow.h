#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class QString;
class QLabel;
class Timer;
class TimerWindow:public QDialog
{
	Q_OBJECT
	public:
		explicit TimerWindow(QWidget *parent = 0);
		~TimerWindow();
	private:
		QLabel *m_plblDisp;
		Timer *m_pTimer;

		QAction *exitAct;
	private slots:

	public slots:
		void slotTimeTick(int);
		void slotShowStat();
	signals:
};

#endif
