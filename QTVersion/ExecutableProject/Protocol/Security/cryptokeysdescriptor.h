#ifndef SECURITYKEYSPAIR_H
#define SECURITYKEYSPAIR_H


#include "cryptokey.h"
#include <QDateTime>



struct CryptoKeysDescriptor
{
    CryptoKeysDescriptor(CryptoKey publicKey, CryptoKey privateKey);


    CryptoKeysDescriptor();


    CryptoKey publicKey;


    CryptoKey privateKey;


    QDateTime created;
};

#endif // SECURITYKEYSPAIR_H
