#include "rsageneratorsingletron.h"



QMutex RSAGeneratorSingletron::getInstanceMutex;


RSAGeneratorSingletron *RSAGeneratorSingletron::instance;



RSAGeneratorSingletron::RSAGeneratorSingletron(): QObject(nullptr)
{
    keys = (CryptoKeysDescriptor*)malloc(sizeof (CryptoKeysDescriptor));
    updateKeysTimer = new QTimer();
    updateKeysTimer->connect(updateKeysTimer, &QTimer::timeout,this, &RSAGeneratorSingletron::regenerateKeys);
    updateKeysTimer->setInterval(60 * 1000);
    updateKeysTimer->start();
    regenerateKeys();
}


RSAGeneratorSingletron::~RSAGeneratorSingletron()
{
    delete updateKeysTimer;
    delete generator;
    delete  keys;
}


void RSAGeneratorSingletron::regenerateKeys()
{
    qDebug("Обновление RSA ключей!");

    *this->keys = generator->generateSecurityKeys();
}


const CryptoKey RSAGeneratorSingletron::_get_self_private_key(CryptoKey client_key)
{
    return keys->privateKey;
}


const CryptoKey RSAGeneratorSingletron::_get_self_public_key(CryptoKey client_key)
{
    return keys->publicKey;
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
