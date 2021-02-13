#include "protocolhandler.h"


ProtocolHandler::ProtocolHandler()
{

}

QString ProtocolHandler::handleRequest(QJsonArray request_list)
{
    status = ProtocolHandlerStatus::notHandled;

    QJsonObject firstRequest = request_list[0].toObject();
    operation = firstRequest["operation"].toInt();

    QString response_str = "";
    switch (operation) {
        case RequestPattern::handshake:
            response_str = handleHandshake(firstRequest);
        break;
        case RequestPattern::data:
            response_str = handleData(firstRequest);
        break;
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

QString ProtocolHandler::handleHandshake(QJsonObject reqeust_obj)
{
    request_scenario = RequestPattern::handshake;
    response_scenario = ResponsePattern::toClient;

}

QString ProtocolHandler::handleData(QJsonObject request_obj)
{

}
