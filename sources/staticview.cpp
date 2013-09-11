#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>

#include "staticview.h"

StaticView::StaticView(QWidget *parent) : QMainWindow(parent){
    QWidget *centralwidget = new QWidget();
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
        sdb.setDatabaseName("db_name.sqlite");
    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
    }
    QSqlTableModel *model = new QSqlTableModel;
         model->setTable("static");
         model->setEditStrategy(QSqlTableModel::OnManualSubmit);
         model->select();

    QTableView *view = new QTableView;
             view->setModel(model);
             view->setEditTriggers(QAbstractItemView::NoEditTriggers);

     QHBoxLayout *horizontalLayout = new QHBoxLayout(centralwidget);
         horizontalLayout->addWidget(view);
    this->setCentralWidget(centralwidget);
    setWindowIcon(QIcon("./icon.png"));
    setWindowTitle("Pomidorka Static");
}
