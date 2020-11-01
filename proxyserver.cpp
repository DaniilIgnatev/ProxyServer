#include "proxyserver.h"



ProxyServer::ProxyServer(QObject *parent): QTcpServer(parent)
{

}


void ProxyServer::startServer(){
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port)){
        qDebug() << "Could not start server";
    }
    else{
        qDebug() << "Listening to port " << port << "...";
    }
}


void ProxyServer::incomingConnection(qintptr socketDescriptor){
    qDebug() << socketDescriptor << " Connecting...";

    ProxySession *thread = new ProxySession(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
