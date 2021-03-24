#include "securityhandler.h"



SecurityHandler::SecurityHandler(RSACryptoProxy *cryptoProxy, QObject *parent): QObject(parent)
{
    this->cryptoProxy = cryptoProxy;
}


QString SecurityHandler::getPublicKey()
{
     CryptoKey key = cryptoProxy->getPublicKey();
     return key.toString();
}


bool SecurityHandler::checkAuthorize(SHAuthorizeRequest authorize)
{
    qint64 unixTimeNow = QDateTime::currentMSecsSinceEpoch();
    qint64 unixTimeRequest = authorize.time.toUInt();
    return unixTimeNow == unixTimeRequest;
}


SHNakedRequest SecurityHandler::removeShell(SHCryptoDataRequest secured_request)
{
    QString secured_str = secured_request.request;
    QString decrypted_request = cryptoProxy->decrypt(secured_str);

    SHNakedRequest result(secured_request, decrypted_request);

    return result;
}


SHCryptoDataResponse SecurityHandler::putInShell(QString unsecured_response)
{
    SHCryptoDataResponse response;

    QString secured_Str = cryptoProxy->encrypt(unsecured_response);
    response.response = secured_Str;

    return response;
}
