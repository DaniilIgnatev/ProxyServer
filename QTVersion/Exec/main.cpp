#include <QCoreApplication>
#include "../ProxyServer/server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.listen(QHostAddress::Any,8090);

    return a.exec();
}
