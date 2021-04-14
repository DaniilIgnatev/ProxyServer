#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H


#include "../request.h"
#include "../response.h"
#include <QObject>
#include "rsakeypair.h"
#include "rsacryptoproxy.h"
#include "cryptokey.h"
#include <QDateTime>



class SecurityHandler: public QObject
{
    Q_OBJECT
private:
    RSACryptoProxy* cryptoProxy;

public:
    explicit SecurityHandler(RSACryptoProxy *cryptoProxy, QObject *parent = nullptr);


    QString getPublicKey();


    SHNakedRequest removeShell(SHCryptoDataRequest secured_request);


    SHCryptoDataResponse putInShell(QString unsecured_response, bool secure);
};

#endif // SECURITYHANDLER_H
