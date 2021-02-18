#include "server.h"

Server::Server()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Session* client = new Session(socketDescriptor);
}

