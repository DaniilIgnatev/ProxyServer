#ifndef KEYPAIR_H
#define KEYPAIR_H


#include <QString>
#include "cryptokey.h"
#include "rsagenerator.h"
#include "rsageneratorsingletron.h"



struct RSAKeyPair
{
private:

    bool stored = false;


    CryptoKey _self_private_key;


    CryptoKey _self_public_key;


public:
    CryptoKey get_self_private_key();


    CryptoKey get_self_public_key();


    CryptoKey client_public_key;


    RSAKeyPair(QString client_public_key);


    RSAKeyPair(CryptoKey client_public_key, CryptoKey self_public_key, CryptoKey self_private_key);
};

#endif // KEYPAIR_H
