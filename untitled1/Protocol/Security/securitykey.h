#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>
#include <QChar>
#include <QStringList>



struct SecurityKey
{
    int x;

    int y;

    SecurityKey(int x, int y);

    ///Внимание! Ключи-строки в 16-м коде
    SecurityKey(QString key);

    ///Внимание! Ключи-строки в 16-м коде
    QString toString();
};

#endif // SECURITYKEY_H
