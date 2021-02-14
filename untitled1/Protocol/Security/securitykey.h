#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>



struct SecurityKey
{
    int x;

    int y;

    SecurityKey(QString key);

    QString toString();
};

#endif // SECURITYKEY_H
