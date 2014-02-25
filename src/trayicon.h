#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>

class QAction;
class QMenu;
class TrayIcon : public QObject
{
	Q_OBJECT
private:
	QAction *m_pactExit;

	QMenu *createMenu();

public:
	explicit TrayIcon(QObject *parent = 0);
signals:
	void sigExit();
	void sigTimerSignal(bool bTimeOut=false);
public slots:
	void slotExit();
	void slotTimerSignal();
};

#endif // TRAYICON_H
