#include "server.h"



Settings Server::settings()
{
    QString configPath = _settings.configPath();
    qDebug() << "ini file path: " << configPath;
    return this->_settings;
}


Server::Server(QObject *parent): QTcpServer(parent)
{
    _settings.read();
}


bool Server::listen()
{
    if (this->_settings.hasProxyPort() && this->settings().initialized()){
        this->_listening = this->QTcpServer::listen(QHostAddress::Any, _settings.proxyPort());
        return _listening;
    }
    else{
        this->_listening = false;
        return _listening;
    }
}


QString Server::startupInfo()
{
    QString info = "";

    if (this->_listening){
        info += " Server listening\n";
    }
    else{
        info += " Server start error\n";
    }

    info += "\n" + settings().diagnostics();

    return info;
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor, settings());
}

