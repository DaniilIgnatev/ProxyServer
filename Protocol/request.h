#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>



class SHRequest : public QObject
{
    Q_OBJECT
public:
    QString type = "request";

    QString operation;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHCryptoHandshakeRequest: public SHRequest{
    Q_OBJECT
public:
    QString operation = "cryptoHandshake";

    int method = 0;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHSecuredRequest: public SHRequest{
    Q_OBJECT
public:
    QString UID;

    bool stayAlive;

    QString request;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHAuthorizeRequest: public SHRequest{
    Q_OBJECT
public:
    QString user;

    QString password;

    QString time;
};



class SHClearRequest: public SHSecuredRequest{
    Q_OBJECT
public:
    SHAuthorizeRequest authorizeRequest;

    SHRequest dataRequest;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // REQUEST_H
