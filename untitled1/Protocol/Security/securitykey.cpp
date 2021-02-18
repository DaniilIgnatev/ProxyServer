#include "securitykey.h"



SecurityKey::SecurityKey(int x, int y)
{
    this->x = x;
    this->y = y;
}


SecurityKey::SecurityKey(QString key)
{
     QStringList parts = key.split(QChar('_'));
     bool status;
     this->x = parts[0].toInt(&status,16);
     this->y = parts[1].toInt(&status,16);
}


QString SecurityKey::toString()
{
    return QString::number(x, 16) + QString("_") + QString::number(y, 16);
}
