#ifndef SECURITYKEYSPAIR_H
#define SECURITYKEYSPAIR_H


#include "cryptokey.h"



struct CryptoKeysDescriptor
{
    CryptoKeysDescriptor(CryptoKey publicKey, CryptoKey privateKey);


    CryptoKey publicKey;


    CryptoKey privateKey;
};

#endif // SECURITYKEYSPAIR_H
