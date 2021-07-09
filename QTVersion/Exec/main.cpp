#include <QCoreApplication>
#include "../ProxyServer/server.h"
#include <QtDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    bool started = server.listen();
    qDebug() << server.startupInfo().toUtf8();

    if (started){
        return a.exec();
    }
    else{
        QThread::sleep(5);
        return -1;
    }
}
