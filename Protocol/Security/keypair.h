#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <QWidget>

struct Key
{
public:
    int x;

    int y;

    Key(QString key);

    QString toString();
};



class RSAKeyPair : public QObject
{
    Q_OBJECT
public:
    Key self_private_key;

    Key self_public_key;

    Key client_public_key;

    RSAKeyPair(QString client_public_key);
};

#endif // KEYPAIR_H
