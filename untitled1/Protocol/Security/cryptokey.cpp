#include "cryptokey.h"



bool CryptoKey::isEmpty()
{
    return x > 0 && y > 0;
}


CryptoKey::CryptoKey(int x, int y)
{
    this->x = x;
    this->y = y;
}


CryptoKey::CryptoKey(QString key)
{
    this->x = 0;
    this->y = 0;

    if (key.count() > 0){
        QStringList parts = key.split(QChar('_'));
        if (parts.count() == 2){
            bool status;
            this->x = parts[0].toInt(&status,16);
            this->y = parts[1].toInt(&status,16);
        }
    }
}


QString CryptoKey::toString()
{
    return QString::number(x, 16) + QString("_") + QString::number(y, 16);
}
