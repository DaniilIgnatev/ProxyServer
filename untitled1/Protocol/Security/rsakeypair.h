#ifndef KEYPAIR_H
#define KEYPAIR_H



#include <QString>
#include "securitykey.h"



struct RSAKeyPair
{
    SecurityKey self_private_key = SecurityKey(QString());


    SecurityKey self_public_key = SecurityKey(QString());


    SecurityKey client_public_key = SecurityKey(QString());


    RSAKeyPair(SecurityKey client_public_key);


    RSAKeyPair();
};

#endif // KEYPAIR_H
