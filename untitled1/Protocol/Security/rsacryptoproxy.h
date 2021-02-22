#ifndef RSACRYPTOPROXY_H
#define RSACRYPTOPROXY_H

#include <QObject>
#include "rsakeypair.h"


class RSACryptoProxy : public QObject
{
    Q_OBJECT
public:

    RSAKeyPair keys = RSAKeyPair(SecurityKey(QString()));


    RSACryptoProxy(RSAKeyPair keys, QObject* parent = nullptr);


    QString encrypt(QString str);


    QString decrypt(QString str);

};

#endif // RSACRYPTOPROXY_H

