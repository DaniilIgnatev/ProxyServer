#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include <QtDebug>
#include <QTcpSocket>



enum ProxyRequestPattern{
    handshake, data
};



enum ProxyResponsePattern{
    toClient, toServer
};

//QJsonDocument::fromRawData. Вызывать, чтобы проверить что документ пришел целиком


class ProxySession : public QThread
{
    Q_OBJECT
//THREAD
public:
    explicit ProxySession(qintptr ID, QObject *parent = 0);

    void run() override;


//SH_CLIENT
private:
    QTcpSocket *client_socket;

    qintptr client_Socket_ID;

    void client_on_complete();


public: signals:
    void client_error (QTcpSocket::SocketError socketError);


public slots:
    void client_package();

    void client_disconnect();


//SH_SERVER
private:
    QTcpSocket *server_socket;

    qintptr server_Socket_ID;

    void server_on_complete();

public: signals:
    void server_error (QTcpSocket::SocketError socketError);

public slots:
    void server_package();

    void server_disconnect();
};

#endif // MYTHREAD_H







