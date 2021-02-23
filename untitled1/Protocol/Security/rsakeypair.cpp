#include "rsakeypair.h"



RSAKeyPair::RSAKeyPair(QString client_public_key)
{
    this->client_public_key = new CryptoKey(client_public_key);

    RSAGenerator *generator = new RSAGenerator(nullptr);
    CryptoKeysDescriptor keys = generator->generateSecurityKeys();

    this->self_private_key = new CryptoKey(keys.privateKey);
    this->self_public_key = new CryptoKey(keys.publicKey);

    generator->deleteLater();
}


RSAKeyPair::~RSAKeyPair()
{
    if (this->client_public_key != nullptr){
        delete this->client_public_key;
        this->client_public_key = nullptr;
    }

    if (this->self_private_key != nullptr){
        delete this->self_private_key;
        this->self_private_key = nullptr;
    }

    if (this->self_public_key != nullptr){
        delete this->self_public_key;
        this->self_public_key = nullptr;
    }
}

