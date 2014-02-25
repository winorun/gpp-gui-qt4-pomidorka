#include <QApplication>
#include <QDesktopWidget>


#include "timerwindow.h"
#include "setting.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(resources);
	QApplication app(argc, argv);
//	app.setStyle("Plastique");
//	app.setOrganizationName("Trolltech");
    app.setApplicationName("Pomidorka");// <-- edit

	QFont font;
	font.setPointSize(50);

	Setting *mSetting=Setting::Instance();
	mSetting->setValue("font",font.toString());
	mSetting->setValue("time","1500:300:2000");
	mSetting->setValue("pos","500:500");
	mSetting->setValue("file","statistics");

	TimerWindow *m_pWindowsTimer = new TimerWindow(app.desktop());
	m_pWindowsTimer->show();

	return app.exec();
}
