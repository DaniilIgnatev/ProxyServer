#include "proxysession.h"



ProxySession::ProxySession(qintptr ID, QObject *parent): QThread(parent)
{
    this->socketDescriptor = ID;
}


void ProxySession::run(){
    qDebug() << "Thread started";

    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(this->socketDescriptor)){
        emit error(socket -> error());
        return;
    }

    //Direct connection -- invoke slot immedeately
    connect(socket, SIGNAL(readyRead()), this, SLOT(client_on_data()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(client_on_disconnect()));

    qDebug() << socketDescriptor << " Client connected";

    exec();
}


void ProxySession::client_on_data(){
    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << Data;

    socket->write(Data);
}


void ProxySession::client_on_disconnect(){
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
