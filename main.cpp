#include <QCoreApplication>
#include "proxyserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyServer server;
    server.startServer();

    return a.exec();
}
