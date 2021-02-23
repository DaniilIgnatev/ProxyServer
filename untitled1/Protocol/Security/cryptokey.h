#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>
#include <QChar>
#include <QStringList>



struct CryptoKey
{
    int x;

    int y;

    CryptoKey(int x, int y);

    ///Внимание! Ключи-строки в 16-м коде
    CryptoKey(QString key);

    ///Внимание! Ключи-строки в 16-м коде
    QString toString();
};

#endif // SECURITYKEY_H
