#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include "QJsonArray"
#include "QJsonObject"
#include "request.h"
#include "response.h"
#include <QJsonDocument>
#include <QException>
#include "Security/securityhandler.h"
#include "Security/rsacryptoproxy.h"
#include "Security/rsakeypair.h"
#include <QtDebug>
#include "Security/cryptokey.h"
#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include "json_extension.h"
#include <QTimer>



enum ProtocolHandlerStatus{
    notHandled = 0, error = 1, handled = 2
};



///Предоставляет внутренний интерфейс для клиента
class ProtocolHandler : public QObject
{
    Q_OBJECT
public:

    ProtocolHandler(QObject *parent = nullptr);


    ~ProtocolHandler();

signals:
    void responseReady(QByteArray &responseData);

public slots:
    void handleRequest(QByteArray &requestData);
    void shDataSocket_onError(QAbstractSocket::SocketError);
    void shDataSocket_onConnected();
    void shDataSocket_onDisconnected();
    void shDataSocket_onReadyRead();
    void onReadDataTimeout();
private:

    QTcpSocket* shDataSocket = nullptr;


    QTimer* onReadDataTimer = nullptr;


    QByteArray* bytesToServer = nullptr;


    quint32 bytes_read = 0;


    QByteArray* readData = nullptr;


    QDataStream* readStream = nullptr;


    void processResponse();


    SecurityHandler* security_handler = nullptr;


    ProtocolPattern_Enum request_scenario = ProtocolPattern_Enum::unknown;


    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;


    bool stayAlive = false;


    bool secureResponse = false;


    void handleCryptoHandshakeRequest(QJsonObject &reqeust_obj);


    void handleCryptoDataRequest(QJsonObject &request_obj);


    void handleUnknownRequest(QJsonObject &request_obj);


    void handleException(QException &e,QAbstractSocket::SocketError errorCode = QAbstractSocket::SocketError::TemporaryError);
};

#endif // PROTOCOLHANDLER_H
