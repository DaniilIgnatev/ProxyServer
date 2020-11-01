#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = nullptr);

signals:

};

#endif // REQUEST_H
