#ifndef SECURITYHANDLER_H
#define SECURITYHANDLER_H

#include <QObject>

class SecurityHandler : public QObject
{
    Q_OBJECT
public:
    explicit SecurityHandler(QObject *parent = nullptr);

signals:

};

#endif // SECURITYHANDLER_H
