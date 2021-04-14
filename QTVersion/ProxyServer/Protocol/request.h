#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


///Любой запрос
struct SHRequest{
    QString type = "request";

    QString operation;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



///Запрос организации защищенного канала связи
struct SHCryptoHandshakeRequest: SHRequest{
    QString operation = "cryptoHandshake";

    int method = 0;

    QString key;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



///Зашифрованый запрос бизнес-логики
struct SHCryptoDataRequest: SHRequest{

    bool stayAlive;

    bool secureResponse;

    QString request;

    QString key;

    void read(const QJsonObject &json);

    void write(QJsonObject &json);
};



///Полностью раскрытый запрос
struct SHNakedRequest: SHCryptoDataRequest{
    SHNakedRequest(const SHCryptoDataRequest& dataRequest, QString decryptedRequest);

    QString decryptedRequest;
};

#endif // REQUEST_H
