#include <QApplication>
#include <QIcon>

#include "mainwindow.h"
#include "staticview.h"
#include "timer.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(res);
	QApplication app(argc, argv);
//	app.setStyle("Plastique");
	//app.setOrganizationName("Trolltech");
    app.setApplicationName("Pomidorka");// <-- edit


	MainWindow mainWin;
    StaticView windowsStaticView(&mainWin);
    Timer myTimer;
    QObject::connect(&mainWin,SIGNAL(timerStart()),&myTimer,SLOT(slotTimerStart()));
    QObject::connect(&mainWin,SIGNAL(timerStop()),&myTimer,SLOT(slotTimerStop()));
    QObject::connect(&myTimer,SIGNAL(sigTimeTick(int,int)),&mainWin,SLOT(timeTick(int,int)));
    QObject::connect(&mainWin,SIGNAL(sigStaticView()),&windowsStaticView,SLOT(show()));
	mainWin.show();
	return app.exec();
}
