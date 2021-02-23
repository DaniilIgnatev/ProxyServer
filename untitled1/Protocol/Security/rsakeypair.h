#ifndef KEYPAIR_H
#define KEYPAIR_H



#include <QString>
#include "cryptokey.h"
#include "rsagenerator.h"



class RSAKeyPair
{
public:
    CryptoKey* self_private_key = nullptr;


    CryptoKey* self_public_key = nullptr;


    CryptoKey* client_public_key = nullptr;


    RSAKeyPair(QString client_public_key);


    ~RSAKeyPair();

};

#endif // KEYPAIR_H
