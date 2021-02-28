#include "testrsacryptoproxy.h"



TestRSACryptoProxy::TestRSACryptoProxy(QObject *parent) : QObject(parent)
{

}


void TestRSACryptoProxy::initTestCase()
{

}


void TestRSACryptoProxy::cleanupTestCase()
{
    if (cryptoProxy != nullptr){
        cryptoProxy->deleteLater();
    }
}


void TestRSACryptoProxy::encryptDecrypt()
{
    RSAKeyPair rsaKeys(CryptoKey(187,2059),CryptoKey(187,2059), CryptoKey(283,2059));

    cryptoProxy = new RSACryptoProxy(rsaKeys);
    QString message = "ПРИВЕТ";

    QString encrypted = cryptoProxy->encrypt(message);
    QString decrypted = cryptoProxy->decrypt(encrypted);
    QCOMPARE(message.toUtf8(), decrypted.toUtf8());
}
