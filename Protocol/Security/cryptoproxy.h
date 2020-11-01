#ifndef CRYPTOPROXY_H
#define CRYPTOPROXY_H

#include <QObject>

class CryptoProxy : public QObject
{
    Q_OBJECT
public:
    explicit CryptoProxy(QObject *parent = nullptr);

signals:

};

#endif // CRYPTOPROXY_H
