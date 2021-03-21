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


qint64 hashString(const QString & str)
{
  QByteArray hash = QCryptographicHash::hash(
    QByteArray::fromRawData((const char*)str.utf16(), str.length()*2),
    QCryptographicHash::Md5
  );
  Q_ASSERT(hash.size() == 16);
  QDataStream stream(hash);
  qint64 a, b;
  stream >> a >> b;
  return a ^ b;
}


uint CryptoKey::qHash(CryptoKey key)
{
    QString str = (QString(key.x) + QString(key.y));
    qint64 hash = hashString(str);
    return hash;
}



