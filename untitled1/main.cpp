#include <QCoreApplication>
#include "server.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.listen(QHostAddress::Any,5000);

    return a.exec();
}
