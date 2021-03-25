#include <QCoreApplication>
#include "server.h"
#include <QDebug>
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Main thread id = " << QThread::currentThreadId();

    Server server;
    server.listen(QHostAddress::Any, 8090);

    return a.exec();
}
