#ifndef PROXYSERVICE_H
#define PROXYSERVICE_H

#include <QCoreApplication>
#include "qtservice/qtservice.h"

#include "../ProxyServer/server.h"
#include <QFile>

class ProxyService : public QtService<QCoreApplication>
{
public:
    explicit ProxyService(int argc, char **argv);

    void start();

    void stop();

    void pause();

    void resume();

private:
    Server *server;
};

#endif // PROXYSERVICE_H
