#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QJsonObject>



#define RequestPattern_undefined "undefined"
#define RequestPattern_handshake "cryptoHandshake"
#define RequestPattern_data "cryptoData"



///Цель общения с клиентом
enum RequestPattern_Enum{
    unknown,
    cryptoHandshake,
    cryptoData
};



///Цель общения с клиентом, логика
struct RequestPattern {
    RequestPattern_Enum type;

    RequestPattern(QString operation);

    QString toOperation();
};



///Любой запрос
class SHRequest : public QObject{
    Q_OBJECT
public:
    QString type = "request";

    QString operation;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



///Запрос организации защищенного канала связи
class SHCryptoHandshakeRequest: public SHRequest{
    Q_OBJECT
public:
    QString operation = "cryptoHandshake";

    int method = 0;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



///Запрос доступа к данным
class SHSecuredRequest: public SHRequest{
    Q_OBJECT
public:
    QString UID;

    bool stayAlive;

    QString request;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



///Запрос авторизации серверу данных
class SHAuthorizeRequest: public SHRequest{
    Q_OBJECT
public:
    QString user;

    QString password;

    QString time;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



///Полностью раскрытый запрос
class SHNakedRequest: public SHSecuredRequest{
    Q_OBJECT
public:
    SHAuthorizeRequest authorizeRequest;

    SHRequest dataRequest;
};

#endif // REQUEST_H
