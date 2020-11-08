#ifndef CRYPTOPROXY_H
#define CRYPTOPROXY_H

#include "keypair.h"
#include <QObject>

class RSACryptoProxy : public QObject
{
    Q_OBJECT
public:
    RSAKeyPair keys;

    RSACryptoProxy(RSAKeyPair keys);

    QString encrypt(QString str);

    QString decrypt(QString str);
};

#endif // CRYPTOPROXY_H
