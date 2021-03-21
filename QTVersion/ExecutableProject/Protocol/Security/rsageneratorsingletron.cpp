#include "rsageneratorsingletron.h"



QMutex RSAGeneratorSingletron::getInstanceMutex;


RSAGeneratorSingletron *RSAGeneratorSingletron::instance;



RSAGeneratorSingletron::RSAGeneratorSingletron(): QObject(nullptr)
{
    updateKeysTimer = new QTimer();
    updateKeysTimer->connect(updateKeysTimer, &QTimer::timeout,this, &RSAGeneratorSingletron::regenerateKeys);
    updateKeysTimer->setInterval(60 * 1000);
    updateKeysTimer->start();

    debugKeys = (CryptoKeysDescriptor*)malloc(sizeof (CryptoKeysDescriptor));
    regenerateKeys();
}


RSAGeneratorSingletron::~RSAGeneratorSingletron()
{
    delete updateKeysTimer;
    delete generator;
    delete  debugKeys;
}


void RSAGeneratorSingletron::regenerateKeys()
{
    qDebug("Обновление RSA ключей!");

    //добавить обновление словаря
    *this->debugKeys = generator->generateSecurityKeys();
}


const CryptoKey RSAGeneratorSingletron::_get_self_private_key(CryptoKey client_key)
{
    //CryptoKeysDescriptor serverKeys = this->clientToKeysMap.value(client_key);
    //CryptoKey serverPrivateKey = serverKeys.privateKey;

    return debugKeys->privateKey;
}


const CryptoKey RSAGeneratorSingletron::_get_self_public_key(CryptoKey client_key)
{
    CryptoKeysDescriptor serverKeys = this->clientToKeysMap.value(client_key);
    //CryptoKey serverPublicKey = serverKeys.publicKey;

    return debugKeys->publicKey;
}


//STATIC


RSAGeneratorSingletron *RSAGeneratorSingletron::getInstance()
{
    getInstanceMutex.lock();
    if (instance == nullptr){
        instance = new RSAGeneratorSingletron();
    }
    getInstanceMutex.unlock();

    return instance;
}


const CryptoKey RSAGeneratorSingletron::get_self_private_key(CryptoKey client_key)
{
    return instance->_get_self_private_key(client_key);
}


const CryptoKey RSAGeneratorSingletron::get_self_public_key(CryptoKey client_key)
{
    return instance->_get_self_public_key(client_key);
}
