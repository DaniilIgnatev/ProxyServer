#include "proxysession.h"



ProxySession::ProxySession(qintptr ID, QObject *parent): QThread(parent)
{
    this->client_Socket_ID = ID;
}


void ProxySession::run(){
    qDebug() << "Thread started";

    client_socket = new QTcpSocket();

    if (!client_socket->setSocketDescriptor(this->client_Socket_ID)){
        emit client_error(client_socket -> error());
        return;
    }

    //Direct connection -- invoke slot immedeately
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(client_on_data()), Qt::DirectConnection);
    connect(client_socket, SIGNAL(disconnected()), this, SLOT(client_on_disconnect()));

    qDebug() << client_Socket_ID << " Client connected";

    exec();
}



//CLIENT_SOCKET
void ProxySession::client_package(){
    QByteArray Data = client_socket->readAll();

    qDebug() << client_Socket_ID << " Data in: " << Data;

    client_socket->write(Data);
}


void ProxySession::client_on_complete(){

}


void ProxySession::client_disconnect(){
    qDebug() << client_Socket_ID << " Disconnected";

    client_socket->deleteLater();
    exit(0);
}



//SERVER_SOCKET
void ProxySession::server_package(){

}


void ::ProxySession::server_on_complete(){

}


void ProxySession::server_disconnect(){

}
