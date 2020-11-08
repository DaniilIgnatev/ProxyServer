#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H


#include "cryptoproxy.h"
#include "../request.h"
#include "../response.h"
#include <QObject>


class SecurityHandler : public QObject
{
    Q_OBJECT
public:
    explicit SecurityHandler(RSACryptoProxy cryptoProxy);

    RSACryptoProxy cryptoProxy;

    SHClearRequest removeShell(SHSecuredRequest secured_request);

    bool checkAuthorize(SHAuthorizeRequest authorize);

    SHCryptoDataResponse putInShell(QString str, QString operation);
};

#endif // SECURITYHANDLER_H
