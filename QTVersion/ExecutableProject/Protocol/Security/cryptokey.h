#ifndef SECURITYKEY_H
#define SECURITYKEY_H



#include <QString>
#include <QChar>
#include <QStringList>



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


    //добавить qhash, ==, <

    friend bool operator <(const CryptoKey& lhs, const CryptoKey& rhs){
        return lhs.x + lhs.y < rhs.x + rhs.y;
    }


    friend bool operator >(const CryptoKey& lhs, const CryptoKey& rhs){
        return lhs.x + lhs.y > rhs.x + rhs.y;
    }
};

#endif // SECURITYKEY_H
