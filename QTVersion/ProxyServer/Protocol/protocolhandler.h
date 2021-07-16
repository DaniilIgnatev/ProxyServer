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
#include "../json_extension.h"
#include <QTimer>
#include "../settings.h"
#include "../logwriter.h"



#define ON_READ_TIMEOUT_MS 100


enum ProtocolHandlerStatus{
    notHandled = 0, error = 1, handled = 2
};



///Предоставляет внутренний интерфейс для клиента
class ProtocolHandler : public QObject
{
    Q_OBJECT
public:

    ProtocolHandler(Settings* settings, LogWriter* logWriter, QObject *parent = nullptr);


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

    LogWriter* logWriter;


    Settings* settings;


    //RESPONSE
    QTcpSocket* shDataSocket = nullptr;


    QTimer* onReadDataTimer = nullptr;


    QByteArray* bytesToServer = nullptr;


    quint32 bytes_read = 0;


    QByteArray* readData = nullptr;


    QDataStream* readStream = nullptr;


    void processResponse();


    //REQUEST
    QJsonObject *request = nullptr;


    SecurityHandler* security_handler = nullptr;


    ProtocolPattern_Enum request_scenario = ProtocolPattern_Enum::unknown;


    ProtocolHandlerStatus status = ProtocolHandlerStatus::notHandled;


    bool stayAlive = false;


    bool secureResponse = false;



    //CRYPTO HANDSHAKE REQUEST
    SHCryptoHandshakeRequest *cryptoHandshakeRequest = nullptr;


    void handleCryptoHandshakeRequest(QJsonObject &reqeust_obj);


    //CRYPTO DATA REQUEST
    SHCryptoDataRequest *cryptoDataRequest = nullptr;


    void handleCryptoDataRequest(QJsonObject &request_obj);


    //UNKNOWN REQUEST
    void handleUnknownRequest(QJsonObject &request_obj);


    //EXCEPTION
    void handleException(QException &e,QAbstractSocket::SocketError errorCode = QAbstractSocket::SocketError::TemporaryError);
};

#endif // PROTOCOLHANDLER_H
