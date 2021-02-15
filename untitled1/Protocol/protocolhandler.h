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



///Предоставляет внутренний интерфейс для клиента
class ProtocolHandler : public QObject
{
    Q_OBJECT
public:
    ProtocolHandler(QObject *parent = nullptr);

signals:
    void responseReady(QByteArray response);

public slots:
    QString handleRequest(QByteArray request_list);

private:
    SecurityHandler* security_handler = NULL;

    Storage* storage = NULL;

    ~ProtocolHandler();

    ProtocolPattern_Enum request_scenario = ProtocolPattern_Enum::unknown;

    DestinationPattern_Enum response_scenario = DestinationPattern_Enum::unknown;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    bool stayAlive = false;

    QByteArray handleCryptoHandshakeRequest(QJsonObject reqeust_obj);

    QByteArray handleCryptoDataRequest(QJsonObject request_obj);

    QByteArray handleUnknownRequest(QJsonObject request_obj);
};

#endif // PROTOCOLHANDLER_H
