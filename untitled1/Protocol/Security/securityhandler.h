#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H


#include "../request.h"
#include "../response.h"
#include <QObject>
#include "rsakeypair.h"
#include "rsacryptoproxy.h"
#include "securitykey.h"



class SecurityHandler: QObject
{
    Q_OBJECT
private:
    RSACryptoProxy* cryptoProxy;

public:
    explicit SecurityHandler(RSACryptoProxy &cryptoProxy, QObject *parent = nullptr);

    QString serverKey();

    SHNakedRequest removeShell(SHCryptoDataRequest secured_request);

    bool checkAuthorize(SHAuthorizeRequest authorize);

    SHCryptoDataResponse putInShell(QString str, QString operation);
};

#endif // SECURITYHANDLER_H
