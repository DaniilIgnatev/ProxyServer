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
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " Client connected";

    exec();
}


void ProxySession::readyRead(){
    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << Data;

    socket->write(Data);
}


void ProxySession::disconnected(){
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
