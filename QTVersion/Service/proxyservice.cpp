#include "proxyservice.h"



ProxyService::ProxyService(int argc, char **argv): QtService<QCoreApplication>(argc, argv, "SHPROXYSERVER")
{
    setServiceDescription("Security server for INTERRA smart house system");
}


void ProxyService::start()
{
    QCoreApplication *app = application();
    server = new Server(app);

    server->listen();
    QtService::instance()->logMessage(server->startupInfo());
}


void ProxyService::stop()
{
    QtService::instance()->logMessage("stop");
    this->server->close();
    this->server->deleteLater();
}


void ProxyService::pause()
{
    QtService::instance()->logMessage("pause");
}


void ProxyService::resume()
{
    QtService::instance()->logMessage("resume");
}
