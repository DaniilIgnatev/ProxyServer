#include "protocolhandler.h"


ProtocolHandler::ProtocolHandler(QObject *parent): QObject(parent)
{
    storage = new Storage(this);
}


ProtocolHandler::~ProtocolHandler()
{

}


QString ProtocolHandler::handleRequest(QJsonArray request_list)
{
    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    QString operation = firstRequest["operation"].toString();

    ProtocolPattern requestType(operation);
    QString response_str = "";

    try {
        switch (requestType.type) {
        case ProtocolPattern_Enum::cryptoHandshake:
            response_str = QString(handleCryptoHandshakeRequest(firstRequest));
            break;
        case ProtocolPattern_Enum::cryptoData:
            response_str = QString(handleCryptoDataRequest(firstRequest));
            break;
        default:
           response_str = QString(handleUnknownRequest(firstRequest));
        }
    }  catch (QException e) {

    }

    return response_str;
}


QByteArray ProtocolHandler::handleCryptoHandshakeRequest(QJsonObject request_obj)
{
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;
    response_scenario = DestinationPattern_Enum::toClient;

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
    return result;
}


QByteArray ProtocolHandler::handleCryptoDataRequest(QJsonObject request_obj)
{
    request_scenario = ProtocolPattern_Enum::cryptoData;
    response_scenario = DestinationPattern_Enum::toServer;

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


QByteArray ProtocolHandler::handleUnknownRequest(QJsonObject request_obj)
{
    SHStatusResponse unknownRequest;
    unknownRequest.result_message = "error";
    unknownRequest.result_message = "unknown request type";
    QJsonObject jsonObject;
    unknownRequest.write(jsonObject);

    QJsonDocument jsonDocument(jsonObject);
    QByteArray result = jsonDocument.toJson(QJsonDocument::JsonFormat::Compact);

    status = ProtocolHandlerStatus::error;
    return result;
}
