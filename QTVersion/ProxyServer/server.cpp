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
        this->_listening = this->QTcpServer::listen(QHostAddress::Any, _settings.proxyPort());
        return _listening;
    }
    else{
        qDebug() << "Settings are missing the port value";
        this->_listening = false;
        return _listening;
    }
}


QString Server::startupInfo()
{
     QString info = "";

    if (this->_listening){
        info += " Server listening\n";
        info += " hasProxyServerPort: " + QString::number(serverPort()) + "\n";
        info += " hasSHServerPort: " + QString::number(settings().shPort()) + "\n";
    }
    else{
        info += " Server start error\n";
        info += " hasProxyServerPort: " + QVariant(settings().hasProxyPort()).toString() + "; value: " + QString::number(settings().proxyPort()) + "\n";
        info += " hasSHServerPort: " + QVariant(settings().hasSHPort()).toString() + "; value: " + QString::number(settings().shPort()) + "\n";
    }

    return info;
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor, this->_settings.shPort());
}

