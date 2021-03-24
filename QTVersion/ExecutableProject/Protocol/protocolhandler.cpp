#include "protocolhandler.h"



ProtocolHandler::ProtocolHandler(QObject *parent): QObject(parent)
{

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
}


void ProtocolHandler::handleRequest(QByteArray &requestData)
{
    qDebug() << "handleRequest " << QThread::currentThreadId();

    QJsonDocument requestDocument = QJsonDocument::fromJson(requestData);
    QJsonArray request_list = requestDocument.array();

    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
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


void ProtocolHandler::handleCryptoHandshakeRequest(QJsonObject &request_obj)
{
    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;

    SHCryptoHandshakeRequest handshake;
    handshake.read(request_obj);

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

    emit singleResponseReady(result);
}


//CRYPTO_DATA
void ProtocolHandler::handleCryptoDataRequest(QJsonObject &request_obj)
{
    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoData;

    SHCryptoDataRequest securedRequest;
    securedRequest.read(request_obj);

    this->stayAlive = securedRequest.stayAlive;

    RSAKeyPair keyPair(securedRequest.key);
    RSACryptoProxy *crypto = new RSACryptoProxy(keyPair);
    security_handler = new SecurityHandler(crypto, this);
    crypto->setParent(security_handler);

    SHNakedRequest nakedRequest = security_handler->removeShell(securedRequest);
    bytesToServer = new QByteArray(nakedRequest.decryptedRequest.toUtf8());

    shDataSocket = new QTcpSocket(this);
    connect(shDataSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&ProtocolHandler::shDataSocket_onError);
    connect(shDataSocket, &QTcpSocket::connected, this, &ProtocolHandler::shDataSocket_onConnected);
    connect(shDataSocket, &QTcpSocket::disconnected, this, &ProtocolHandler::shDataSocket_onDisconnected);
    connect(shDataSocket, &QTcpSocket::readyRead, this, &ProtocolHandler::shDataSocket_onReadyRead);
    shDataSocket->connectToHost("95.68.243.66", 8084);
}


void ProtocolHandler::shDataSocket_onError(QAbstractSocket::SocketError errorCode)
{
    if (errorCode != QAbstractSocket::SocketError::RemoteHostClosedError){
        QException exception;
        handleException(exception, errorCode);
    }
}


void ProtocolHandler::shDataSocket_onConnected()
{
    qDebug("shDataSocket_onConnected");

    shDataSocket->write(*bytesToServer);

    if (!stayAlive){
        onReadDataTimer = new QTimer(this);
        onReadDataTimer->setSingleShot(true);
        connect(onReadDataTimer, &QTimer::timeout, this, &ProtocolHandler::onReadDataTimeout);
        onReadDataTimer->start(500);
    }

    delete bytesToServer;
    bytesToServer = nullptr;
}


void ProtocolHandler::shDataSocket_onDisconnected()
{
    qDebug("shDataSocket_onDisconnected");
    qDebug("shDataSocket disconnected");

    qDebug() << "Сервер УД завершил обмен данными";
    qDebug() << bytes_read;
    qDebug() << " байт.";

    qDebug() << "shDataSocket_onDisconnected thread id" << QThread::currentThreadId();

    qDebug() << readData;

    QString unsecuredResponse = QString::fromUtf8(*readData);
    SHCryptoDataResponse securedResponse = security_handler->putInShell(unsecuredResponse);

    QJsonObject responseObject;
    securedResponse.write(responseObject);
    QJsonDocument responseDocument(responseObject);
    QByteArray responseData = responseDocument.toJson(QJsonDocument::JsonFormat::Compact);

    emit singleResponseReady(responseData);
}


void ProtocolHandler::shDataSocket_onReadyRead()
{
    qDebug("shDataSocket_onReadyRead");

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

    qDebug() << "Получено ";
    qDebug() << bytes_read;
    qDebug() << " байт.";

    if (stayAlive){
        SHCryptoDataResponse securedResponse = security_handler->putInShell();
    }
}


void ProtocolHandler::onReadDataTimeout(){
    qDebug("onReadDataTimeout");
    shDataSocket->close();
}


void ProtocolHandler::handleUnknownRequest(QJsonObject &request_obj)
{
    qDebug("handleUnknownRequest");

    status = ProtocolHandlerStatus::error;

    qDebug(QJsonDocument(request_obj).toJson());

    SHStatusResponse unknownResponse;
    unknownResponse.result_message = "error";
    unknownResponse.result_message = "unknown request type";

    QJsonObject jsonObject;
    unknownResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);



    emit singleResponseReady(result);
}


void ProtocolHandler::handleException(QException &e, QAbstractSocket::SocketError errorCode)
{
    status = ProtocolHandlerStatus::error;

    qDebug("Error: handleRequest");
    qDebug(e.what());

    SHStatusResponse exceptionResponse;
    exceptionResponse.result_message = "error";
    exceptionResponse.result_message = "exception occured";
    exceptionResponse.result_message.append(qPrintable(e.what()));

    QJsonObject jsonObject;
    exceptionResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact).data();

    emit singleResponseReady(result);
}
