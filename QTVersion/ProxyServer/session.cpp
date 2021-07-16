#include "session.h"


Session::Session(quint16 socketDescriptor, Settings* settings): QObject(0)
{
    this->socketDescriptor = socketDescriptor;

    thread = new QThread();
    thread->start();
    connect(this->thread, &QThread::finished, this, &Session::deleteLater);

    //log
    QString logDirPath = settings->logsPath();
    logWriter = new LogWriter(logDirPath, QString::number(socketDescriptor), this);
    logWriter->log("SESSION INIT");

    //protocolHandler
    protocolHandler = new ProtocolHandler(settings, logWriter, this);
    connect(this, &Session::requestReady, protocolHandler, &ProtocolHandler::handleRequest);
    connect(protocolHandler,&ProtocolHandler::responseReady, this, &Session::handleResponse);

    //client socket
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    logWriter->log("SOCKET OPENED");

    connect(socket, &QTcpSocket::disconnected, this, &Session::socketClosed);
    connect(socket, &QTcpSocket::readyRead, this, &Session::readyRead);

    this->moveToThread(thread);
}


Session::~Session()
{
    logWriter->log("SESSION DEINIT");
    socket->deleteLater();
    protocolHandler->deleteLater();
    logWriter->deleteLater();
    delete readData;
    delete readStream;
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

            logWriter->log("READY READ ", false);
            logWriter->log(QString::number(request_size).toUtf8(), false);
            logWriter->log(" BYTES.", false);
        }
        else{
            return;
        }
    }

    quint32 bytes_read_add = socket->bytesAvailable();

    QByteArray newReadData = socket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;

    logWriter->log("ACCUMULATED ", false);
    logWriter->log(QString::number(bytes_read).toUtf8(), false);
    logWriter->log(" bytes.", false);


    if (request_size == bytes_read){
        logWriter->log("PACKAGE FETCHED ");
        logWriter->log(QString::number(request_size).toUtf8());
        logWriter->log(" BYTES.");

        logWriter->log("THREAD ID:");
        logWriter->log(QString::number((uint64_t)QThread::currentThreadId()).toUtf8());
        logWriter->log("READ DATA:\n");

        logWriter->log(readData);

        emit requestReady(*readData);

        delete readData;
        readData = NULL;
        delete readStream;
        readStream = NULL;
        request_size = 0;
        bytes_read = 0;
    }
}


void Session::handleResponse(QByteArray &response)
{
    JSON_Extension::makeResponseArray(response);
    //qDebug("%s",response.data());

    response_size = response.size();
    response.insert(0,(char*)&response_size,4);
    logWriter->log("RESPONSE DATA:\n");
    socket->write(response);
}


void Session::socketClosed()
{
    logWriter->log("SOCKET CLOSED");
    this->thread->exit();
}
