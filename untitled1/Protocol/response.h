#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>



///Направление ответа
enum ResponsePattern_Enum {
    unknown,
    toClient,
    toServer
};



class SHResponse{
public:
    QString type = "response";

    QString operation;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHCryptoHandshakeResponse{
public:
    QString operation = "cryptoHandshake";

    QString UUID;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHCryptoDataResponse{
public:
    QString response;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



class SHDataResponse{
public:
    QString result;//был any

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};


class SHStatusResponse{
public:
    bool result = true;

    QString result_message;

    QString description;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // RESPONSE_H
