#include "protocolhandler.h"



ProtocolHandler::ProtocolHandler(QObject *parent): QObject(parent)
{

}


ProtocolHandler::~ProtocolHandler()
{

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

    QString serverKey = security_handler->getPublicKey();

    SHCryptoHandshakeResponse response;
    response.key = serverKey;

    QJsonObject jsonObject = QJsonObject();
    response.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    emit responseReady(result);
}


void ProtocolHandler::handleCryptoDataRequest(QJsonObject &request_obj)
{
    status = ProtocolHandlerStatus::handled;
    request_scenario = ProtocolPattern_Enum::cryptoData;

    SHCryptoDataRequest request;
    request.read(request_obj);

    this->stayAlive = request.stayAlive;

    shDataSocket = new QTcpSocket(this);
    connect(shDataSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&ProtocolHandler::shDataSocket_onError);
    connect(shDataSocket, &QTcpSocket::connected, this, &ProtocolHandler::shDataSocket_onConnected);
    connect(shDataSocket, &QTcpSocket::disconnected, this, &ProtocolHandler::shDataSocket_onDisconnected);
    connect(shDataSocket, &QTcpSocket::readyRead, this, &ProtocolHandler::shDataSocket_onReadyRead);
    shDataSocket->connectToHost("95.104.194.120", 8084);
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


}


void ProtocolHandler::shDataSocket_onDisconnected()
{
    qDebug("shDataSocket_onDisconnected");
    qDebug("shDataSocket disconnected");

    qDebug() << "Сервер ответил";
    qDebug() << bytes_read;
    qDebug() << " байт.";

    qDebug() << "shDataSocket_onDisconnected thread id" << QThread::currentThreadId();

    qDebug() << readData;

    emit responseReady(*readData);
}


void ProtocolHandler::shDataSocket_onReadyRead()
{
    qDebug("shDataSocket_onReadyRead");

    if (readData == NULL){
        readData = new QByteArray();
    }
    if (readStream == NULL){
        readStream = new QDataStream(shDataSocket);
    }


    quint32 bytes_read_add = shDataSocket->bytesAvailable();

    QByteArray newReadData = shDataSocket->readAll();
    readData->append(newReadData);
    bytes_read += bytes_read_add;

    qDebug() << "Получено ";
    qDebug() << bytes_read;
    qDebug() << " байт.";
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



    emit responseReady(result);
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

    emit responseReady(result);
}
