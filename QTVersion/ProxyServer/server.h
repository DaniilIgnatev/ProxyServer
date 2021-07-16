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

    Settings* _settings;

    bool _listening = false;

public:
    Settings settings();


    Server(QObject *parent = nullptr);


    ~Server();


    bool listen();


    QString startupInfo();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // PROXYSERVER_H
