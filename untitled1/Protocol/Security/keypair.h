#ifndef KEYPAIR_H
#define KEYPAIR_H



#include <QString>



struct RSAKeyPair
{
    SecurityKey self_private_key;

    SecurityKey self_public_key;

    SecurityKey client_public_key;

    RSAKeyPair(QString client_public_key);
};

#endif // KEYPAIR_H
