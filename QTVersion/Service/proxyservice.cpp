#include "proxyservice.h"



ProxyService::ProxyService(int argc, char **argv): QtService<QCoreApplication>(argc, argv, "SHPROXYSERVER")
{
    setServiceDescription("Security server of INTERRA smart house system");
}


void ProxyService::start()
{
    QCoreApplication *app = application();
    server = new Server(app);
    QtService::instance()->logMessage("listening");
}


void ProxyService::pause()
{
    QtService::instance()->logMessage("pause");
}


void ProxyService::resume()
{
    QtService::instance()->logMessage("resume");
}
