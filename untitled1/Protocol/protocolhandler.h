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
#include "storage.h"



enum ProtocolHandlerStatus{
    notHandled = 0, error = 1, handled = 2
};



class ProtocolHandler : public QObject
{
    Q_OBJECT
public:
    ProtocolHandler(QObject *parent = nullptr);

    QString handleRequest(QJsonArray request_list);

private:
    SecurityHandler* security_handler = NULL;

    Storage storage;

    ~ProtocolHandler();

    ProtocolPattern_Enum request_scenario = ProtocolPattern_Enum::unknown;

    DestinationPattern_Enum response_scenario = DestinationPattern_Enum::unknown;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    bool stayAlive = false;

    QByteArray handleHandshake(QJsonObject reqeust_obj);

    QByteArray handleData(QJsonObject request_obj);

    QByteArray handleUnknown(QJsonObject request_obj);
};

#endif // PROTOCOLHANDLER_H
