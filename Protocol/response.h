#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>

class Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(QObject *parent = nullptr);

signals:

};

#endif // RESPONSE_H
