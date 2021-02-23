#include "rsageneratorsingletron.h"



QMutex RSAGeneratorSingletron::getInstanceMutex;


RSAGeneratorSingletron *RSAGeneratorSingletron::instance;



RSAGeneratorSingletron::RSAGeneratorSingletron()
{
    updateKeysTimer = new QTimer();
    updateKeysTimer->connect(updateKeysTimer, &QTimer::timeout,this, &RSAGeneratorSingletron::updateKeys);
    updateKeysTimer->setInterval(60 * 1000);
    updateKeysTimer->start();
    updateKeys();
}


void RSAGeneratorSingletron::updateKeys()
{
    qDebug("Обновление RSA ключей!");

    if (!self_private_key.isEmpty() && !self_public_key.isEmpty()){
        this->past_private_key = self_private_key;
        this->past_public_key = self_public_key;
    }

    CryptoKeysDescriptor keys = generator->generateSecurityKeys();
    this->self_private_key = keys.privateKey;
    this->self_public_key = keys.publicKey;
}


const CryptoKey RSAGeneratorSingletron::_get_self_private_key()
{
    return self_private_key;
}


const CryptoKey RSAGeneratorSingletron::_get_self_public_key()
{
    return self_public_key;
}


bool RSAGeneratorSingletron::_hasPastKey()
{
    return !past_private_key.isEmpty() && !past_public_key.isEmpty();
}


const CryptoKey RSAGeneratorSingletron::_get_past_private_key()
{
    return past_private_key;
}


const CryptoKey RSAGeneratorSingletron::_get_past_public_key()
{
    return past_public_key;
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


const CryptoKey RSAGeneratorSingletron::get_self_private_key()
{
    return instance->_get_self_private_key();
}


const CryptoKey RSAGeneratorSingletron::get_self_public_key()
{
    return instance->_get_self_public_key();
}


bool RSAGeneratorSingletron::hasPastKey()
{
    return instance->_hasPastKey();
}


const CryptoKey RSAGeneratorSingletron::get_past_private_key()
{
    return instance->_get_past_private_key();
}


const CryptoKey RSAGeneratorSingletron::get_past_public_key()
{
    return instance->_get_past_public_key();
}
