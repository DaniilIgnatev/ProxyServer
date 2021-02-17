#include <QCoreApplication>
#include "server.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.listen(QHostAddress::Any,8084);

    return a.exec();
}
