#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H


#include "rsacrypto.h"
#include "../request.h"
#include "../response.h"
#include <QObject>



class SecurityHandler: QObject
{
    Q_OBJECT
private:
    RSACrypto cryptoProxy;

public:
    explicit SecurityHandler(RSACrypto cryptoProxy, QObject *parent = nullptr);

    QString serverKey();

    SHNakedRequest removeShell(SHCryptoDataRequest secured_request);

    bool checkAuthorize(SHAuthorizeRequest authorize);

    SHCryptoDataResponse putInShell(QString str, QString operation);
};

#endif // SECURITYHANDLER_H
