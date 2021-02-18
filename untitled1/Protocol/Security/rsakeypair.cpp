#include "rsakeypair.h"



RSAKeyPair::RSAKeyPair(SecurityKey client_public_key)
{
    this->client_public_key = client_public_key;
    this->self_private_key = SecurityKey(QString());
    this->self_public_key = SecurityKey(QString());
}

