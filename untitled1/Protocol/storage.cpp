#include "storage.h"
#include <QSqlDatabase>


Storage::Storage(QObject *parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("smarthouse");
    db.setUserName("smarthouse");
    db.setPassword("1234");
    bool ok = db.open();
}
