#include "testrsacryptoproxy.h"



TestRSACryptoProxy::TestRSACryptoProxy(QObject *parent) : QObject(parent)
{

}

void TestRSACryptoProxy::initTestCase()
{
    RSAKeyPair *keyPair = new RSAKeyPair("07_21");
    cryptoProxy = new RSACryptoProxy(keyPair);
}


void TestRSACryptoProxy::cleanupTestCase()
{
    cryptoProxy->deleteLater();
}


void TestRSACryptoProxy::encryptDecrypt()
{
    delete cryptoProxy->keys->self_private_key;
    cryptoProxy->keys->self_private_key = new CryptoKey(283,2059);
    delete cryptoProxy->keys->self_public_key;
    cryptoProxy->keys->self_public_key = new CryptoKey(187,2059);
    delete cryptoProxy->keys->client_public_key;
    cryptoProxy->keys->client_public_key = cryptoProxy->keys->self_public_key;

    QString message = "ПРИВЕТ";

    QString encrypted = cryptoProxy->encrypt(message);
    QString decrypted = cryptoProxy->decrypt(encrypted);
    QCOMPARE(message.toUtf8(), decrypted.toUtf8());
}
