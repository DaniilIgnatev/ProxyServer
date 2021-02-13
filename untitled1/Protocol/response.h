#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>



///Направление ответа
enum ResponsePattern {
    toClient,
    toServer
};



class SHResponse: public QObject{
    Q_OBJECT
public:
    QString type = "response";

    QString operation;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHCryptoHandshakeResponse: public SHResponse{
    Q_OBJECT
public:
    QString operation = "cryptoHandshake";

    QString UUID;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHCryptoDataResponse: public SHResponse{
    Q_OBJECT
public:
    QString response;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHDataResponse: public SHResponse{
    Q_OBJECT
public:
    QString result;//был any

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};


class SHStatusResponse: public SHResponse{
    Q_OBJECT
public:
    bool result = true;

    QString result_message;

    QString description;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // RESPONSE_H
