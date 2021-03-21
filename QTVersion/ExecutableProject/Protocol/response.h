#ifndef RESPONSE_H
#define RESPONSE_H



#include <QObject>
#include "protocolpattern.h"
#include <QJsonObject>



struct SHResponse{
    QString type = "response";

    QString operation;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



struct SHCryptoHandshakeResponse: SHResponse{
    QString operation = ProtocolPattern_handshake;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



struct SHCryptoDataResponse: SHResponse{
    QString operation = ProtocolPattern_data;

    QString response;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};



struct SHStatusResponse: SHResponse{
    bool result = true;

    QString result_message;

    QString description;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // RESPONSE_H
