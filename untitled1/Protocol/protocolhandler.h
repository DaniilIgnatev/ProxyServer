#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include "QJsonArray"
#include "QJsonObject"
#include "request.h"
#include "response.h"
#include <QJsonDocument>
#include <QException>
#include "storage.h"
#include "log.h"
#include "Security/securityhandler.h"
#include "Security/rsacrypto.h"
#include "Security/rsakeypair.h"

#include "Security/securitykey.h"
#include <QThread>




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
    void responseReady(QByteArray* responseData);

public slots:
    void handleRequest(QByteArray &requestData);

private:
    SecurityHandler* security_handler = NULL;

    Storage* storage = NULL;

    ~ProtocolHandler();

    ProtocolPattern_Enum request_scenario = ProtocolPattern_Enum::unknown;

    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;

    bool stayAlive = false;

    void handleCryptoHandshakeRequest(QJsonObject &reqeust_obj);

    void handleCryptoDataRequest(QJsonObject &request_obj);

    void handleUnknownRequest(QJsonObject &request_obj);

    void handleException(QException &e);
};

#endif // PROTOCOLHANDLER_H
