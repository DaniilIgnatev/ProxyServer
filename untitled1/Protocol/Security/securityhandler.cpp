#include "securityhandler.h"



SecurityHandler::SecurityHandler(RSACryptoProxy *cryptoProxy, QObject *parent): QObject(parent)
{
    this->cryptoProxy = cryptoProxy;
}


QString SecurityHandler::serverKey()
{
     CryptoKey key = *(cryptoProxy->keys->self_public_key());
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
    QString clean_str = cryptoProxy->decrypt(secured_str);

    SHNakedRequest result;
    result.operation = secured_request.operation;
    result.request = secured_request.request;
    result.stayAlive = secured_request.stayAlive;

    SHAuthorizeRequest authorizeRequest;

    result.authorizeRequest = authorizeRequest;

    SHCryptoDataRequest dataRequest;
    dataRequest.request = clean_str;

    result.dataRequest = dataRequest;

    return result;
}


SHCryptoDataResponse SecurityHandler::putInShell(QString str, QString operation)
{
    SHCryptoDataResponse response;
    response.operation = operation;

    QString secured_Str = cryptoProxy->encrypt(str);
    response.response = secured_Str;

    return response;
}
