#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H


#include "../request.h"
#include "../response.h"
#include <QObject>
#include "rsakeypair.h"
#include "rsacryptoproxy.h"
#include "cryptokey.h"
#include <QDateTime>



class SecurityHandler: QObject
{
    Q_OBJECT
private:
    RSACryptoProxy* cryptoProxy;

public:
    explicit SecurityHandler(RSACryptoProxy *cryptoProxy, QObject *parent = nullptr);


    QString serverKey();


    bool checkAuthorize(SHAuthorizeRequest authorize);


    SHNakedRequest removeShell(SHCryptoDataRequest secured_request);


    SHCryptoDataResponse putInShell(QString str, QString operation);
};

#endif // SECURITYHANDLER_H
