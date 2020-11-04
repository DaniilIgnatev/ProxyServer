#include "proxyserver.h"


ProxyServer::ProxyServer(QObject *parent): QTcpServer(parent)
{

}


void ProxyServer::startServer(){
    int port = 8085;

    if(!this->listen(QHostAddress::Any, port)){
        qDebug() << "Could not start server";
    }
    else{
        qDebug() << "Listening to port " << port << "...";
    }
}


void ProxyServer::incomingConnection(qintptr socketDescriptor){
    qDebug() << socketDescriptor << " Connecting...";

    ProxySession *sessionThread = new ProxySession(socketDescriptor, this);

    connect(sessionThread, SIGNAL(finished()), sessionThread, SLOT(deleteLater()));

    sessionThread->start();
}

