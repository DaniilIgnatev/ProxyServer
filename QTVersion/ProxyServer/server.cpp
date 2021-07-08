#include "server.h"



Settings Server::settings()
{
    return this->_settings;
}


Server::Server(QObject *parent): QTcpServer(parent)
{
    _settings.read();
}


bool Server::listen()
{
    if (this->_settings.hasProxyPort() && this->_settings.hasSHPort()){
        return this->QTcpServer::listen(QHostAddress::Any, _settings.proxyPort());
    }
    else{
        qDebug() << "Settings are missing the port value";
        return false;
    }
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor, this->_settings.shPort());
}

