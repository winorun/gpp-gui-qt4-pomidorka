#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenu;
class QTextEdit;
class QTextDocument;
class QString;
class MainWindow:public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow();

	private:
		QMenu *menuMain;

        QTextEdit *textEdit;
        QTextDocument *textDocument;

		void createActions();
		void createMenu();
		
		QAction *mStart;
		QAction *mStop;
		QAction *mFont;
        QAction *exitAct;
        QAction *staticView;
	private slots:
		void START();
		void STOP();
		void slotSetFont();
        void slotStaticView();
	public slots:
		void timeTick(int,int);
	signals:
	   void timerStart();
	   void timerStop();
       void sigStaticView();
};

#endif
