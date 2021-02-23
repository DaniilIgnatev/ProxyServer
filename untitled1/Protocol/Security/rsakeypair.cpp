#include "rsakeypair.h"




RSAKeyPair::RSAKeyPair(QString client_public_key)
{
    this->client_public_key = CryptoKey(client_public_key);
}



const CryptoKey RSAKeyPair::get_self_private_key()
{
    return RSAGeneratorSingletron::get_self_private_key();
}


const CryptoKey RSAKeyPair::get_self_public_key()
{
    return RSAGeneratorSingletron::get_self_public_key();
}


bool RSAKeyPair::hasPastKey()
{
    return RSAGeneratorSingletron::hasPastKey();
}


const CryptoKey RSAKeyPair::get_past_private_key()
{
    return RSAGeneratorSingletron::get_past_private_key();
}


const CryptoKey RSAKeyPair::get_past_public_key()
{
    return RSAGeneratorSingletron::get_past_public_key();
}

