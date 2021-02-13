#include "session.h"


Session::Session(quint16 socketDescriptor)
{
    this->socketDescriptor = socketDescriptor;
    start();
}

void Session::send(QString &message)
{
    socket->write(message.toUtf8());
}

void Session::run()
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::disconnected, this, &Session::socketClosed);
    connect(socket, &QTcpSocket::disconnected, this, &Session::deleteLater);
    connect(socket, &QTcpSocket::readyRead, this, &Session::readyRead);

    exec();
}

void Session::readyRead()
{
    QByteArray data = socket->readAll();
    socket->write(data);
}

void Session::socketClosed()
{
    this->exit();
}
