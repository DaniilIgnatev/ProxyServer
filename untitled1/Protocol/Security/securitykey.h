#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>



struct SecurityKey
{
    int x;

    int y;

    ///Внимание! Ключи-строки в 16-м коде
    SecurityKey(QString key);

    ///Внимание! Ключи-строки в 16-м коде
    QString toString();
};

#endif // SECURITYKEY_H
