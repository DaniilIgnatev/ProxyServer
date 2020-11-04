#ifndef MYSERVER_H
#define MYSERVER_H


#include <QTcpServer>
#include "proxysession.h"



class ProxyServer : public QTcpServer
{
        Q_OBJECT
public:

    explicit ProxyServer(QObject *parent = 0);


    void startServer();

signals:


public slots:


protected:
    void incomingConnection(qintptr handle) override;
};

#endif // MYSERVER_H
