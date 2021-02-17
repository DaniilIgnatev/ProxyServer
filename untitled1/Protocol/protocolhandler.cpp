#include "protocolhandler.h"



ProtocolHandler::ProtocolHandler(QObject *parent): QObject(parent)
{
    storage = new Storage(this);
}


ProtocolHandler::~ProtocolHandler()
{

}


void ProtocolHandler::handleRequest(QByteArray* requestData)
{
    QJsonDocument requestDocument = QJsonDocument::fromJson(*requestData);
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
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;

    SHCryptoHandshakeRequest handshake;
    handshake.read(request_obj);

    RSAKeyPair keyPair(handshake.key);
    RSACrypto crypto(keyPair);

    security_handler = new SecurityHandler(crypto,this);
    QString UUID = storage->reserveUUID(handshake);

    QString serverKey = security_handler->serverKey();

    SHCryptoHandshakeResponse response;
    response.UUID = UUID;
    response.key = serverKey;

    QJsonObject jsonObject;
    response.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    status = ProtocolHandlerStatus::handled;
    emit responseReady(&result);
}


void ProtocolHandler::handleCryptoDataRequest(QJsonObject &request_obj)
{
    request_scenario = ProtocolPattern_Enum::cryptoData;

    SHCryptoDataRequest request;
    request.read(request_obj);
    /*
    this.request_scenario = ProxyRequestPattern.data
    this.response_scenario = ProxyResponsePattern.toServer
    response = await this.handleData(firstRequest)
    this.status = ProtocolHandlerStatus.handled
    break
    */

    //подписываюсь на сокет

    status = ProtocolHandlerStatus::handled;
}


void ProtocolHandler::handleUnknownRequest(QJsonObject &request_obj)
{
    Log::debug("handleUnknownRequest");
    Log::debug(QJsonDocument(request_obj).toJson());

    SHStatusResponse unknownResponse;
    unknownResponse.result_message = "error";
    unknownResponse.result_message = "unknown request type";

    QJsonObject jsonObject;
    unknownResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    status = ProtocolHandlerStatus::error;

    emit responseReady(&result);
}


void ProtocolHandler::handleException(QException &e)
{
    Log::info("Error: handleRequest");
    Log::info(qPrintable(e.what()));

    SHStatusResponse exceptionResponse;
    exceptionResponse.result_message = "error";
    exceptionResponse.result_message = "exception occured";
    exceptionResponse.result_message.append(qPrintable(e.what()));

    QJsonObject jsonObject;
    exceptionResponse.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact).data();

    status = ProtocolHandlerStatus::error;

    emit responseReady(&result);
}
