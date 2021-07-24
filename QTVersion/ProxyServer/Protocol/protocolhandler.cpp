#include "protocolhandler.h"



ProtocolHandler::ProtocolHandler(Settings *settings, LogWriter* logWriter, QObject *parent): QObject(parent)
{
    this->settings = settings;
    this->logWriter = logWriter;
}


ProtocolHandler::~ProtocolHandler()
{
    if (readData != nullptr){
        delete readData;
        readData = nullptr;
    }

    if (readStream != nullptr){
        delete readStream;
        readStream = nullptr;
    }

    if (request != nullptr){
        delete request;
        request = nullptr;
    }

    if (cryptoHandshakeRequest != nullptr){
        delete cryptoHandshakeRequest;
        cryptoHandshakeRequest = nullptr;
    }

    if (cryptoDataRequest != nullptr){
        delete cryptoDataRequest;
        cryptoDataRequest = nullptr;
    }

    if (shDataSocket != nullptr){
        shDataSocket->deleteLater();
        shDataSocket = nullptr;
    }

    if (bytesToServer != nullptr){
        delete bytesToServer;
        bytesToServer = nullptr;
    }

    logWriter->log("PROTOCOL HANDLER DEINIT\n", LogWriter::Protocol);
}


void ProtocolHandler::handleRequest(QByteArray &requestData)
{
    //qDebug() << "ProtocolHandler::handleRequest, thread: " << QThread::currentThreadId();

    QJsonDocument requestDocument = QJsonDocument::fromJson(requestData);
    QJsonArray request_list = requestDocument.array();

    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    request = new QJsonObject(firstRequest);

    QString operation = firstRequest["operation"].toString();
    ProtocolPattern requestType(operation);

    try {
        switch (requestType.type) {
        case ProtocolPattern_Enum::cryptoHandshake:
            handleCryptoHandshakeRequest(firstRequest);
            break;
        case ProtocolPattern_Enum::cryptoData:
            handleCryptoDataRequest(firstRequest);
            break;
        default:
            handleUnknownRequest(firstRequest);
        }
    }  catch (QException &e) {
        handleException(e);
    }
}


//CRYPTO_HANDSHAKE
void ProtocolHandler::handleCryptoHandshakeRequest(QJsonObject &request_obj)
{
    logWriter->log("ProtocolHandler::handleCryptoHandshakeRequest\n", LogWriter::Protocol);

    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHCryptoHandshakeRequest handshake;
    handshake.read(request_obj);
    cryptoHandshakeRequest = new SHCryptoHandshakeRequest(handshake);

    RSAKeyPair keyPair(handshake.key);
    RSACryptoProxy *crypto = new RSACryptoProxy(keyPair);

    security_handler = new SecurityHandler(crypto, this);
    crypto->setParent(security_handler);

    QString serverKey = security_handler->getPublicKey();

    SHCryptoHandshakeResponse response;
    response.key = serverKey;

    QJsonObject jsonObject = QJsonObject();
    response.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    emit responseReady(result);
}


//CRYPTO_DATA
void ProtocolHandler::handleCryptoDataRequest(QJsonObject &request_obj)
{
    logWriter->log("ProtocolHandler::handleCryptoDataRequest\n", LogWriter::Protocol);

    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoData;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHCryptoDataRequest dataRequest;
    dataRequest.read(request_obj);
    cryptoDataRequest = new SHCryptoDataRequest(dataRequest);

    this->stayAlive = dataRequest.stayAlive;
    this->secureResponse = dataRequest.secureResponse;

    RSAKeyPair keyPair(dataRequest.key);
    RSACryptoProxy *crypto = new RSACryptoProxy(keyPair);
    security_handler = new SecurityHandler(crypto, this);
    crypto->setParent(security_handler);

    SHNakedRequest nakedRequest = security_handler->removeShell(dataRequest);
    bytesToServer = new QByteArray(nakedRequest.decryptedRequest.toUtf8());

    shDataSocket = new QTcpSocket(this);
    connect(shDataSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&ProtocolHandler::shDataSocket_onError);
    connect(shDataSocket, &QTcpSocket::connected, this, &ProtocolHandler::shDataSocket_onConnected);
    connect(shDataSocket, &QTcpSocket::disconnected, this, &ProtocolHandler::shDataSocket_onDisconnected);
    connect(shDataSocket, &QTcpSocket::readyRead, this, &ProtocolHandler::shDataSocket_onReadyRead);
    shDataSocket->connectToHost(this->settings->shAdress(), this->settings->shPort());
}


//UNKNOWN_REQUEST
void ProtocolHandler::handleUnknownRequest(QJsonObject &request_obj)
{
    logWriter->log("ProtocolHandler::handleUnknownRequest\n", LogWriter::Protocol);

    status = ProtocolHandlerStatus::error;

    //qDebug("%s",QJsonDocument(request_obj).toJson().data());

    SHStatusResponse unknownResponse;
    unknownResponse.result_message = "error";
    unknownResponse.result_message = "unknown request type";

    QJsonObject jsonObject;
    unknownResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    emit responseReady(result);
}


//EXCEPTION
void ProtocolHandler::handleException(QException &e, QAbstractSocket::SocketError errorCode)
{
    logWriter->log("ProtocolHandler::handleException: ", LogWriter::Protocol);
    logWriter->log((QString(e.what()) + "\n").toUtf8(), LogWriter::Protocol);

    status = ProtocolHandlerStatus::error;

    SHStatusResponse exceptionResponse;
    exceptionResponse.result_message = "error";
    exceptionResponse.result_message = "exception occured";
    exceptionResponse.result_message.append(qPrintable(e.what()));

    QJsonObject jsonObject;
    exceptionResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact).data();

    emit responseReady(result);
}



//SH_SOCKET_EVENTS
void ProtocolHandler::shDataSocket_onConnected()
{
    logWriter->log("ProtocolHandler::shDataSocket_onConnected\n", LogWriter::Status);

    if (bytesToServer != nullptr && bytesToServer->length() > 0){
        shDataSocket->write(*bytesToServer);

        logWriter->log("SH SOCKET DID WRITE\n", LogWriter::Status);
        logWriter->log("BYTES: ", LogWriter::Status);
        logWriter->log(QString::number(bytesToServer->size()).toUtf8() + "\n", LogWriter::Status);

        logWriter->log("\nCONTENT:\n", LogWriter::Content);
        logWriter->log(bytesToServer, LogWriter::Content);
        logWriter->log("\n\n", LogWriter::Content);
    }

    if (bytesToServer != nullptr){
        delete bytesToServer;
        bytesToServer = nullptr;
    }
}


void ProtocolHandler::shDataSocket_onDisconnected()
{
    logWriter->log("ProtocolHandler::shDataSocket_onDisconnected\n", LogWriter::Status);
    processResponse();
}


void ProtocolHandler::shDataSocket_onReadyRead()
{
    logWriter->log("ProtocolHandler::shDataSocket_onReadyRead\n", LogWriter::Status, false);

//    if (!stayAlive){
//        if (onReadDataTimer == nullptr){
//            onReadDataTimer = new QTimer(this);
//            onReadDataTimer->setSingleShot(true);
//            connect(onReadDataTimer, &QTimer::timeout, this, &ProtocolHandler::onReadDataTimeout);
//            onReadDataTimer->start(ON_READ_TIMEOUT_MS);
//        }
//        else{
//            onReadDataTimer->start(ON_READ_TIMEOUT_MS);
//        }
//    }


    if (readData == nullptr){
        readData = new QByteArray();
    }
    if (readStream == nullptr){
        readStream = new QDataStream(shDataSocket);
    }

    quint32 bytes_read_add = shDataSocket->bytesAvailable();

    QByteArray newReadData = shDataSocket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;
    timeoutTimes = 0;

    if (stayAlive){
        processResponse();
    }
}


//void ProtocolHandler::onReadDataTimeout(){
//    timeoutTimes++;
//    logWriter->log("ProtocolHandler::onReadDataTimeout, timeout times: " + QString::number(timeoutTimes).toUtf8() + "\n", LogWriter::Status);

//    if (bytes_read > 0 && (!readData->endsWith("}]" && readData->startsWith("[{")))){
//        if (timeoutTimes * ON_READ_TIMEOUT_MS < ON_READ_MAX_TIMEOUT_DATA_MS){
//            logWriter->log("MORE BYTES ARE AVAILABLE", LogWriter::Status);
//            //onReadDataTimer->start(ON_READ_TIMEOUT_MS);
//        }
//        else{
//            logWriter->log("CRYTICAL TIMEOUT WITH SOME DATA", LogWriter::Status);
//            shDataSocket->close();
//        }
//    }
//    else{
//        if (timeoutTimes * ON_READ_TIMEOUT_MS >= ON_READ_MAX_TIMEOUT_EMPTY_MS){
//            logWriter->log("CRYTICAL TIMEOUT WITHOUT ANY DATA", LogWriter::Status);
//            shDataSocket->close();
//        }
//    }
//}


void ProtocolHandler::shDataSocket_onError(QAbstractSocket::SocketError errorCode)
{
    if (errorCode != QAbstractSocket::SocketError::RemoteHostClosedError){
        QException exception;
        handleException(exception, errorCode);
    }
}


void ProtocolHandler::processResponse(){
    if (bytes_read > 0){
        QString unsecuredResponse = QString::fromUtf8(*readData);
        readData->clear();
        bytes_read = 0;
        timeoutTimes = 0;

        SHCryptoDataResponse dataResponse = security_handler->putInShell(unsecuredResponse, secureResponse);
        QJsonObject responseObject;
        dataResponse.write(responseObject);

        QJsonDocument responseDocument(responseObject);
        QByteArray responseData = responseDocument.toJson(QJsonDocument::JsonFormat::Compact);

        emit responseReady(responseData);
    }
}
