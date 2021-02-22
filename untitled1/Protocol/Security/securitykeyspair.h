#ifndef SECURITYKEYSPAIR_H
#define SECURITYKEYSPAIR_H


#include "securitykey.h"



class SecurityKeysPair
{
public:
    SecurityKeysPair(SecurityKey publicKey, SecurityKey privateKey);


    SecurityKey publicKey;


    SecurityKey privateKey;
};

#endif // SECURITYKEYSPAIR_H
