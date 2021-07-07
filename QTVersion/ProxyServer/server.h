#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include "session.h"
#include "settings.h"


class Server : public QTcpServer
{
    Q_OBJECT
private:
    Settings settings;

public:
    Server(QObject *parent = nullptr);


    bool listen();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // PROXYSERVER_H
