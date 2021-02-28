#include "rsakeypair.h"




RSAKeyPair::RSAKeyPair(QString client_public_key)
{
    this->client_public_key = CryptoKey(client_public_key);
    this->stored = false;
}


RSAKeyPair::RSAKeyPair(CryptoKey client_public_key, CryptoKey self_public_key, CryptoKey self_private_key)
{
    this->client_public_key = client_public_key;
    this->_self_public_key = self_public_key;
    this->_self_private_key = self_private_key;
    this->stored = true;
}


CryptoKey RSAKeyPair::get_self_private_key()
{
    if (stored) {
        return _self_private_key;
    }
    else {
        return RSAGeneratorSingletron::get_self_private_key(this->client_public_key);
    }
}


CryptoKey RSAKeyPair::get_self_public_key()
{
    if (stored){
        return _self_public_key;
    }
    else{
        return RSAGeneratorSingletron::get_self_public_key(this->client_public_key);
    }
}
