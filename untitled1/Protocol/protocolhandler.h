#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include "Security/securityhandler.h"
#include "session.h"
#include "QJsonArray"
#include "QJsonObject"
#include "request.h"
#include "response.h"
#include <QJsonDocument>
#include <QException>



enum ProtocolHandlerStatus{
    notHandled = 0, error = 1, handled = 2
};



class ProtocolHandler : public QObject
{
    Q_OBJECT
private:
    SecurityHandler* secirity_handler = NULL;

    RequestPattern_Enum request_scenario = RequestPattern_Enum::unknown;

    ResponsePattern_Enum response_scenario = ResponsePattern_Enum::unknown;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    ~ProtocolHandler();

    QString operation;

public:
    ProtocolHandler();

    QString handleRequest(QJsonArray request_list);

private:
    bool stayAlive = false;

    QByteArray handleHandshake(QJsonObject reqeust_obj);

    QByteArray handleData(QJsonObject request_obj);

    QByteArray handleUnknown(QJsonObject request_obj);
};

#endif // PROTOCOLHANDLER_H
