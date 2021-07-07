#include "server.h"



Server::Server(QObject *parent): QTcpServer(parent)
{
    settings.read();
}


bool Server::listen()
{
    if (this->settings.hasPort()){
        return this->QTcpServer::listen(QHostAddress::Any, settings.port());
    }
    else{
        qDebug() << "Settings are missing the port value";
        return false;
    }
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor);
}

