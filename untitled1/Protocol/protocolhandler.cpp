#include "protocolhandler.h"


ProtocolHandler::ProtocolHandler()
{

}

QString ProtocolHandler::handleRequest(QJsonArray request_list)
{
    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    operation = firstRequest["operation"].toString();

    RequestPattern requestType(operation);
    QString response_str = "";

    try {
        switch (requestType.type) {
            case RequestPattern_Enum::cryptoHandshake:
                response_str = QString(handleHandshake(firstRequest));
            break;
            case RequestPattern_Enum::cryptoData:
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

    /*


        let error_response = new Response.SHStatusResponse();
        error_response.operation = this.operation

        let response = null
        //try {
            switch (this.operation) {
                case ProxyRequestPattern.handshake:
                    this.request_scenario = ProxyRequestPattern.handshake
                    this.response_scenario = ProxyResponsePattern.toClient
                    response = await this.handleHandshake(firstRequest)
                    this.status = ProtocolHandlerStatus.handled
                    break
                default:
                    this.request_scenario = ProxyRequestPattern.data
                    this.response_scenario = ProxyResponsePattern.toServer
                    response = await this.handleData(firstRequest)
                    this.status = ProtocolHandlerStatus.handled
                    break
            }
        */

    return response_str;
}

QByteArray ProtocolHandler::handleHandshake(QJsonObject reqeust_obj)
{
    request_scenario = RequestPattern_Enum::cryptoHandshake;
    response_scenario = ResponsePattern_Enum::toClient;


//    let handshakeRequest = new Request.SHCryptoHandshakeRequest()
//            handshakeRequest.key = request_obj.key
//            handshakeRequest.method = request_obj.method


//            let method = CryptoProxyMethods[CryptoProxyMethods[handshakeRequest.method]]
//            let key_pair = new RSAKeyPair(handshakeRequest.key)
//            let proxy = new RSACryptoProxy(key_pair)

//            this.security_handler = new SecurityHandler(method, proxy)

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
    request_scenario = RequestPattern_Enum::cryptoData;
    response_scenario = ResponsePattern_Enum::toServer;

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
