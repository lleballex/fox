#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite3");
    db.open();

    MainWindow w;
    w.show();
    return a.exec();
}
