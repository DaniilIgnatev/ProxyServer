#include "session.h"


Session::Session(quint16 socketDescriptor,QObject* parent): QThread(parent)
{
    this->socketDescriptor = socketDescriptor;
    start();
}


Session::~Session()
{
    socket->deleteLater();
    protocol->deleteLater();
    delete readData;
    delete readStream;
}



void Session::send(QString &message)
{
    socket->write(message.toUtf8());
}


void Session::run()
{
    connect(this, &QThread::finished, this, &Session::deleteLater);

    protocol = new ProtocolHandler();

    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::disconnected, this, &Session::socketClosed);
    connect(socket, &QTcpSocket::readyRead, this, &Session::readyRead);

    exec();
}





void Session::readyRead()
{
    if (readData == NULL){
        readData = new QByteArray();
    }
    if (readStream == NULL){
        readStream = new QDataStream(socket);
    }

    QByteArray newReadData = socket->readAll();

    if (request_size == bytes_read){
        emit requestReady(readData);
        delete readData;
        readData = NULL;
        delete readStream;
        readStream = NULL;
    }
}


void Session::handleResponse(QByteArray* response)
{
    socket->write(*response);
}


void Session::socketClosed()
{
    this->exit();
}
