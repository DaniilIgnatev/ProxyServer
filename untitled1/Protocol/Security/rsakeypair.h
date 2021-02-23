#ifndef KEYPAIR_H
#define KEYPAIR_H



#include <QString>
#include "cryptokey.h"
#include "rsagenerator.h"
#include "rsageneratorsingletron.h"



struct RSAKeyPair
{
    const CryptoKey get_self_private_key();


    const CryptoKey get_self_public_key();


    bool hasPastKey();


    const CryptoKey get_past_private_key();


    const CryptoKey get_past_public_key();


    CryptoKey client_public_key;


    RSAKeyPair(QString client_public_key);
};

#endif // KEYPAIR_H
