#ifndef RESPONSE_H
#define RESPONSE_H



#include <QObject>
#include "protocolpattern.h"
#include <QJsonObject>



struct SHResponse{
    QString type = "response";

    QString operation;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



struct SHCryptoHandshakeResponse: SHResponse{

    SHCryptoHandshakeResponse();

    QString key;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



struct SHCryptoDataResponse: SHResponse{

    SHCryptoDataResponse();

    QString response;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



struct SHStatusResponse: SHResponse{

    SHStatusResponse();

    bool result = true;

    QString result_message;

    QString description;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};

#endif // RESPONSE_H
