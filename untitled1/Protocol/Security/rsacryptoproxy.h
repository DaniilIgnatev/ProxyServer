#ifndef RSACRYPTOPROXY_H
#define RSACRYPTOPROXY_H

#include <QObject>
#include "rsakeypair.h"



class RSACryptoProxy : public QObject
{
    Q_OBJECT
private:

    int powBig(int num, int exp, int mod);


    QString enCrypt(QString str, CryptoKey publicKey);


    QString deCrypt(QString str, CryptoKey privateKey);


    RSAKeyPair keys;

public:

    RSACryptoProxy(RSAKeyPair keys, QObject* parent = nullptr);


    RSAKeyPair getKeys();


    QString getPublicKey();


    QString encrypt(QString str);


    QString decrypt(QString base64String);

};

#endif // RSACRYPTOPROXY_H
