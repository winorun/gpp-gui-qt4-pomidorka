#include <QtGui>
#include <QSystemTrayIcon>
#include <QX11Info>

#include "mainwindow.h"

MainWindow::MainWindow()
{
	QFont font;
		font.setPointSize(50);
	QWidget *centralwidget = new QWidget();
    textDocument = new QTextDocument("5:00");
		textDocument->setDefaultFont(font);

	textEdit = new QTextEdit(centralwidget);
//		textEdit->setFrameStyle(QFrame::NoFrame);
		textEdit->setReadOnly(true);
		textEdit->setDocument(textDocument);
		textEdit->setContextMenuPolicy(Qt::CustomContextMenu);

	QHBoxLayout *horizontalLayout = new QHBoxLayout(centralwidget);
		horizontalLayout->addWidget(textEdit);
	this->setCentralWidget(centralwidget);

	createActions();
	createMenu();

	QSystemTrayIcon *trayicon = new QSystemTrayIcon();
		trayicon->setToolTip ("Pomidorka");
		trayicon->setIcon(QIcon(":image/icon.png"));
		trayicon->show();
		trayicon->setContextMenu(menuMain);

	setWindowIcon(QIcon(":image/icon.png"));
	setWindowTitle("Pomidorka");
	setEnabled(false);

			//~ window->move(0,120);
		//~ window->resize(350,450);
	QPalette pal = palette();
		pal.setColor( QPalette::Window, Qt::transparent );
		pal.setColor( QPalette::Button, Qt::transparent );
		pal.setColor( QPalette::Base, Qt::transparent );
		pal.setColor( QPalette::Light, Qt::transparent );
		pal.setColor( QPalette::Midlight, Qt::transparent );
		pal.setColor( QPalette::Dark, Qt::transparent );
		pal.setColor( QPalette::Mid, Qt::transparent );
		pal.setColor( QPalette::Shadow, Qt::transparent );

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setPalette(pal);
}

void MainWindow::createActions()
 {
	exitAct = new QAction(tr("E&xit"), this);
		exitAct->setShortcuts(QKeySequence::Quit);
		exitAct->setStatusTip(tr("Exit the application"));
		connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	mFont = new QAction(tr("F&ont"), this);
		mFont->setStatusTip(tr("Option font"));
		connect(mFont, SIGNAL(triggered()), this, SLOT(slotSetFont()));

	mStart = new QAction(tr("Start"), this);
		mStart->setStatusTip(tr("Start"));
		connect(mStart, SIGNAL(triggered()), this, SLOT(START()));

	mStop = new QAction(tr("Stop"), this);
	mStop->setStatusTip(tr("Stop"));
	mStop->setEnabled(false);
	connect(mStop, SIGNAL(triggered()), this, SLOT(STOP()));

    staticView = new QAction(tr("StaticView"), this);
    staticView->setStatusTip(tr("StaticView"));
    connect(staticView, SIGNAL(triggered()), this, SLOT(slotStaticView()));
 }

void MainWindow::createMenu()
 {
	QMenu *menuOptions = new QMenu();
		menuOptions->setTitle(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));

	//~ QMenu *menuFile = new QMenu(menubar);
		//~ menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));

	menuMain = new QMenu();

	menuOptions->addAction(mFont);
    menuOptions->addAction(staticView);
	menuMain->addAction(mStart);
	menuMain->addAction(mStop);
	menuMain->addMenu(menuOptions);
	menuMain->addAction(exitAct);

 }

void MainWindow::START(){
	mStop->setEnabled(true);
	mStart->setEnabled(false);
    emit timerStart();
	}

void MainWindow::STOP(){
	mStop->setEnabled(false);
	mStart->setEnabled(true);
    emit timerStop();
	}

void MainWindow::slotSetFont(){

	}

void MainWindow::slotStaticView(){
    emit sigStaticView();
}
void MainWindow::timeTick(int iTimeLast, int status){
    int last=iTimeLast;
    int hh=last/60;
    int mm=last%60;
    QString str = QString::number(hh)+":"+QString::number(mm);
    if(status)str="smoko\n"+str;
		textDocument->setPlainText(str);
	}
