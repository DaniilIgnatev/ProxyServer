#include "server.h"

Server::Server(QObject *parent): QTcpServer(parent)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor);
}

