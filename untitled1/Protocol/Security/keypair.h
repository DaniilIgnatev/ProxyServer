#ifndef KEYPAIR_H
#define KEYPAIR_H



#include <QString>



struct RSAKeyPair
{
    QString self_private_key;

    QString self_public_key;

    QString client_public_key;

    RSAKeyPair(QString client_public_key);
};

#endif // KEYPAIR_H
