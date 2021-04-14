#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include "session.h"



class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // PROXYSERVER_H
