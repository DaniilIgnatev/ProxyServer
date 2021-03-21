#include "session.h"


Session::Session(quint16 socketDescriptor): QObject(0)
{
    thread = new QThread();
    thread->start();

    this->socketDescriptor = socketDescriptor;
    connect(this->thread, &QThread::finished, this, &Session::deleteLater);

    protocolHandler = new ProtocolHandler(this);
    connect(this, &Session::requestReady, protocolHandler, &ProtocolHandler::handleRequest);
    connect(protocolHandler,&ProtocolHandler::responseReady, this, &Session::handleResponse);

    //client socket
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    qDebug() << "Socket opened";

    connect(socket, &QTcpSocket::disconnected, this, &Session::socketClosed);
    connect(socket, &QTcpSocket::readyRead, this, &Session::readyRead);

    this->moveToThread(thread);
}


Session::~Session()
{
    socket->deleteLater();
    protocolHandler->deleteLater();
    delete readData;
    delete readStream;
    qDebug() << "Session deinited";
}



void Session::send(QString &message)
{
    socket->write(message.toUtf8());
}


void Session::readyRead()
{
    if (readData == NULL){
        readData = new QByteArray();
    }
    if (readStream == NULL){
        readStream = new QDataStream(socket);
    }

    if (request_size == 0){
        if (socket->bytesAvailable() > 4){
            *readStream >> request_size;
            qDebug() << "Ожидается пакет ";
            qDebug() << request_size;
            qDebug() << " байт.";
        }
        else{
            return;
        }
    }

    quint32 bytes_read_add = socket->bytesAvailable();

    QByteArray newReadData = socket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;

    qDebug() << "Получено ";
    qDebug() << bytes_read;
    qDebug() << " байт.";


    if (request_size == bytes_read){
        qDebug() << "Принят пакет";
        qDebug() << request_size;
        qDebug() << " байт.";

        qDebug() << "readyRead thread id" << QThread::currentThreadId();

        qDebug() << readData;

        emit requestReady(*readData);

        delete readData;
        readData = NULL;
        delete readStream;
        readStream = NULL;
        request_size = 0;
        bytes_read = 0;
    }
}


void Session::handleResponse(QByteArray* response)
{
    response->insert(1,"\"type\":\"response\",");
    response->insert(0,"[");
    response->push_back(']');
    response_size = response->size();
    response->insert(0,(char*)&response_size,4);
    socket->write(*response);
}


void Session::socketClosed()
{
    qDebug() << "socket closed";
    this->thread->exit();
}
