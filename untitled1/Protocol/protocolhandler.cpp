#include "protocolhandler.h"


ProtocolHandler::ProtocolHandler(QObject *parent): QObject(parent)
{

}


ProtocolHandler::~ProtocolHandler()
{

}


QString ProtocolHandler::handleRequest(QJsonArray request_list)
{
    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    operation = firstRequest["operation"].toString();

    ProtocolPattern requestType(operation);
    QString response_str = "";

    try {
        switch (requestType.type) {
            case ProtocolPattern_Enum::cryptoHandshake:
                response_str = QString(handleHandshake(firstRequest));
            break;
            case ProtocolPattern_Enum::cryptoData:
                response_str = QString(handleData(firstRequest));
            break;
        default:
            SHStatusResponse unknownRequest;
            unknownRequest.result_message = "error";
            unknownRequest.result_message = "unknown request type";
            QJsonObject jsonObject;
            unknownRequest.write(jsonObject);

            QJsonDocument jsonDocument(jsonObject);
            response_str = QString(jsonDocument.toJson(QJsonDocument::JsonFormat::Compact));
        }
    }  catch (QException e) {

    }

    return response_str;
}


QByteArray ProtocolHandler::handleHandshake(QJsonObject request_obj)
{
    request_scenario = ProtocolPattern_Enum::cryptoHandshake;
    response_scenario = DestinationPattern_Enum::toClient;

    SHCryptoHandshakeRequest handshake;
    handshake.read(request_obj);

    RSAKeyPair keyPair(handshake.key);
    RSACrypto crypto(keyPair);

    SecurityHandler security(crypto);
//            let UUID = await this.appendUUID(handshakeRequest)
//            let key = this.security_handler.cryptoProxy.keys.server_public_key_string

//            let handshakeResponse = new Response.SHCryptoHandshakeResponse()
//            handshakeResponse.UUID = UUID
//            handshakeResponse.key = key

//            let response = [handshakeResponse]
//            let response_str = JSON.stringify(response)
//            return response_str
//        }

    status = ProtocolHandlerStatus::handled;
}


QByteArray ProtocolHandler::handleData(QJsonObject request_obj)
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

    status = ProtocolHandlerStatus::handled;
}


QByteArray ProtocolHandler::handleUnknown(QJsonObject request_obj)
{


    status = ProtocolHandlerStatus::error;

}
