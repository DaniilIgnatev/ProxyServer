#include "cryptokey.h"



CryptoKey::CryptoKey(int x, int y)
{
    this->x = x;
    this->y = y;
}


CryptoKey::CryptoKey(QString key)
{
     QStringList parts = key.split(QChar('_'));
     bool status;
     this->x = parts[0].toInt(&status,16);
     this->y = parts[1].toInt(&status,16);
}


QString CryptoKey::toString()
{
    return QString::number(x, 16) + QString("_") + QString::number(y, 16);
}
