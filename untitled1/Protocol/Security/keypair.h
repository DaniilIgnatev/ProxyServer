#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <QString>

struct Key
{
public:
    int x;

    int y;

    Key(QString key);

    QString toString();
};



struct RSAKeyPair
{
    Key self_private_key;

    Key self_public_key;

    Key client_public_key;

    RSAKeyPair(QString client_public_key);
};

#endif // KEYPAIR_H
