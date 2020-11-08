#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include "Security/securityhandler.h"
#include "../proxysession.h"


enum ProtocolHandlerStatus{
    notHandled, error, handled
};



class ProtocolHandler : public QObject
{
    Q_OBJECT
private:
    SecurityHandler secirity_handler;

    ProxyRequestPattern request_scenario = ProxyRequestPattern::handshake;

    ProxyResponsePattern response_scenario = ProxyResponsePattern::toClient;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    QString url = "mongodb://localhost:27017/";
    //mongoclient

    ~ProtocolHandler();

    QString operation;
public:
    ProtocolHandler();

    QString handleRequest(QJsonArray request_list);

private:
    QString handleHandshake(QJsonObject reqeust_obj);

    bool stayAlive = false;

    QString handleData(QJsonObject request_obj);

    QString secureResponse(QString message);
};

#endif // PROTOCOLHANDLER_H
