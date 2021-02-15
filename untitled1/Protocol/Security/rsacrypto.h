#ifndef CRYPTOPROXY_H
#define CRYPTOPROXY_H



#include "keypair.h"
#include <QObject>



struct RSACrypto
{
    RSAKeyPair keys;

    RSACrypto(RSAKeyPair keys);

    QString encrypt(QString str);

    QString decrypt(QString str);
};



#endif // CRYPTOPROXY_H
