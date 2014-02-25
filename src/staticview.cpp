#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>

#include "staticview.h"

StaticView::StaticView(QWidget *parent) : QMainWindow(parent){
	QWidget *cwg= new QWidget(this);
	QVBoxLayout *vbox = new QVBoxLayout(cwg);
{
	QHBoxLayout *hbox = new QHBoxLayout();
	QTableView *view = new QTableView(cwg);
		view->setEditTriggers(QAbstractItemView::NoEditTriggers);
		hbox->addWidget(view);

		vbox->addLayout(hbox);
}
{
		QHBoxLayout *hbox = new QHBoxLayout();
		hbox->addStretch();
		{
			QPushButton *ppb = new QPushButton("&Refresh",cwg);
			hbox->addWidget(ppb);
		}
		vbox->addLayout(hbox);
	}
	this->setCentralWidget(cwg);
	setWindowIcon(QIcon(":image/tomatoicon.ico"));
    setWindowTitle("Pomidorka Static");
}


//    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
//        sdb.setDatabaseName("db_name.sqlite");
//    if (!sdb.open()) {
//        qDebug() << sdb.lastError().text();
//    }
//    QSqlTableModel *model = new QSqlTableModel;
//         model->setTable("static");
//         model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//         model->select();
