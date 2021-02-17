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
    Log::debug("Session deinited");
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
    Log::info("Socket opened");

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

    if (request_size == 0){
        if (socket->bytesAvailable() > 4){
            *readStream >> request_size;
            Log::debug("Ожидается пакет ");
            Log::debug(QString(request_size).toLatin1());
            Log::debug(" байт.");
        }
        else{
            return;
        }
    }

    quint32 bytes_read_add = socket->bytesAvailable();

    QByteArray newReadData = socket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;

    Log::debug("Получено ");
    Log::debug(QString(bytes_read).toLatin1());
    Log::debug(" байт.");


    if (request_size == bytes_read){
        Log::debug("Принят пакет");
        Log::debug(QString(request_size).toLatin1());
        Log::debug(" байт.");

        Log::debug(*readData);

        emit requestReady(readData);

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
    socket->write(*response);
}


void Session::socketClosed()
{
    Log::info("socket closed");
    this->exit();
}
