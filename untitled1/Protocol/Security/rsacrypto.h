#ifndef CRYPTOPROXY_H
#define CRYPTOPROXY_H



#include "rsakeypair.h"
#include <QObject>



struct RSACrypto
{
    RSAKeyPair keys = RSAKeyPair(SecurityKey(QString()));

    RSACrypto(RSAKeyPair keys);

    QString encrypt(QString str);

    QString decrypt(QString str);
};



#endif // CRYPTOPROXY_H
