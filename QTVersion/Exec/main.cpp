#include <QCoreApplication>
#include "../ProxyServer/server.h"
#include <QtDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    if (server.listen()){
        qDebug() << "Proxy server listening on port: " << server.serverPort();
        qDebug() << "SHServer port: " << server.settings().shPort();
        return a.exec();
    }
    else{
        qDebug("Server start error");
        QThread::sleep(3);
        return -1;
    }
}
