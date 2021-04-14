#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>
#include <QChar>
#include <QStringList>
#include <QCryptographicHash>
#include <QDataStream>


struct CryptoKey
{
    int x;


    int y;


    bool isEmpty();


    CryptoKey(int x = 0, int y = 0);


    ///Внимание! Ключи-строки в 16-м коде
    CryptoKey(QString key);


    ///Внимание! Ключи-строки в 16-м коде
    QString toString();


    friend bool operator <(const CryptoKey& lhs, const CryptoKey& rhs){
        return lhs.x + lhs.y < rhs.x + rhs.y;
    }


    friend bool operator >(const CryptoKey& lhs, const CryptoKey& rhs){
        return lhs.x + lhs.y > rhs.x + rhs.y;
    }


    friend bool operator ==(const CryptoKey& lhs, const CryptoKey& rhs){
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }


    uint qHash(CryptoKey key);

};

#endif // SECURITYKEY_H
