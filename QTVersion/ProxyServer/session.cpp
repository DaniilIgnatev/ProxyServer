#include "session.h"


Session::Session(quint16 socketDescriptor, Settings* settings): QObject(0)
{
    this->socketDescriptor = socketDescriptor;
    this->settings = settings;

    thread = new QThread();
    thread->start();
    connect(this->thread, &QThread::finished, this, &Session::deleteLater);

    //log
    QString logDirPath = settings->logsPath();
    logWriter = new LogWriter(settings->logsEnabled(), settings->logSocketStatus(), settings->logSocketContent(), logDirPath, QString::number(socketDescriptor), this);

    logWriter->log("Сессия запущена в потоке №", LogWriter::Status);
    logWriter->log(QString::number((uint64_t)thread).toUtf8(), LogWriter::Status);

    //protocolHandler
    protocolHandler = new ProtocolHandler(settings, logWriter, this);
    connect(this, &Session::requestReady, protocolHandler, &ProtocolHandler::handleRequest);
    connect(protocolHandler,&ProtocolHandler::responseReady, this, &Session::handleResponse);

    //client socket
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    logWriter->log(" для клиентского сокета №", LogWriter::Status);
    logWriter->log(QString::number((uint64_t)socketDescriptor).toUtf8() + "\n", LogWriter::Status);

    connect(socket, &QTcpSocket::disconnected, this, &Session::socketClosed);
    connect(socket, &QTcpSocket::readyRead, this, &Session::readyRead);

    this->moveToThread(thread);
}


Session::~Session()
{
    logWriter->log("Деинициализация сессии для потока №", LogWriter::Status);
    logWriter->log(QString::number((uint64_t)thread).toUtf8() , LogWriter::Status);
    logWriter->log(" и сокета №", LogWriter::Status);
    logWriter->log(QString::number((uint64_t)socketDescriptor).toUtf8() + "\n", LogWriter::Status);

    socket->deleteLater();
    protocolHandler->deleteLater();
    delete readData;
    delete readStream;
    logWriter->deleteLater();
    thread->deleteLater();
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

            logWriter->log("Поступил запрос от клиента на: ", LogWriter::Status, false);
            logWriter->log(QString::number(request_size).toUtf8(), LogWriter::Status, false);
            logWriter->log(" байт.", LogWriter::Status, false);
        }
        else{
            return;
        }
    }

    quint32 bytes_read_add = socket->bytesAvailable();

    QByteArray newReadData = socket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;

//    logWriter->log("Получено от клиента ", LogWriter::Status, false);
//    logWriter->log(QString::number(bytes_read).toUtf8(), LogWriter::Status, false);
//    logWriter->log(" байт.", LogWriter::Status, false);


    if (request_size == bytes_read){
//        logWriter->log("\nCLIENT SOCKET READ\n", LogWriter::Status);
//        logWriter->log("BYTES: ", LogWriter::Status);
//        logWriter->log(QString::number(request_size).toUtf8() + "\n", LogWriter::Status);

//        logWriter->log("Тело запроса\n", LogWriter::Content);
//        logWriter->log(readData, LogWriter::Content);
//        logWriter->log("\n\n", LogWriter::Content);

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

    response_size = response.size();
    response.insert(0,(char*)&response_size, 4);

    logWriter->log("Отправил ответ клиенту на ", LogWriter::Status);
    logWriter->log(QString::number(response.size()).toUtf8() + " байт\n\n", LogWriter::Status);

//    logWriter->log("\nCONTENT:\n", LogWriter::Content);
//    logWriter->log(response, LogWriter::Content);
//    logWriter->log("\n\n", LogWriter::Content);

    socket->write(response);
}


void Session::socketClosed()
{
    logWriter->log("Клиентский сокет №" + QString::number((uint64_t)socketDescriptor).toUtf8() + " закрыт\n", LogWriter::Status);
    this->thread->exit();
}
