#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include "Security/securityhandler.h"
#include "session.h"
#include "QJsonArray"
#include "QJsonObject"


enum ProtocolHandlerStatus{
    notHandled = 0, error = 1, handled = 2
};



class ProtocolHandler : public QObject
{
    Q_OBJECT
private:
    SecurityHandler* secirity_handler = NULL;

    RequestPattern request_scenario = RequestPattern::handshake;

    ResponsePattern response_scenario = ResponsePattern::toClient;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    ~ProtocolHandler();

    int operation;

public:
    ProtocolHandler();

    QString handleRequest(QJsonArray request_list);

private:
     bool stayAlive = false;

    QString handleHandshake(QJsonObject reqeust_obj);

    QString handleData(QJsonObject request_obj);
};

#endif // PROTOCOLHANDLER_H
