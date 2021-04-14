#include "cryptokeysdescriptor.h"



CryptoKeysDescriptor::CryptoKeysDescriptor(CryptoKey publicKey, CryptoKey privateKey): publicKey(publicKey),privateKey(privateKey)
{

}


CryptoKeysDescriptor::CryptoKeysDescriptor()
{
    this->privateKey = CryptoKey();
    this->publicKey = CryptoKey();
}
