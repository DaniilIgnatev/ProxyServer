#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include <QtDebug>
#include <QTcpSocket>



enum ProxyrequestPattern{
    handshake, data
};



enum ProxyresponsePattern{
    toClient, toServer
};



class ProxySession : public QThread
{
    Q_OBJECT
//THREAD
public:
    explicit ProxySession(qintptr ID, QObject *parent = 0);

    void run() override;


//SH_CLIENT
private:
    QTcpSocket *socket;

    qintptr socketDescriptor;


public: signals:
    void error (QTcpSocket::SocketError socketError);


public slots:
    void client_on_data();

    void client_on_disconnect();


//SH_SERVER

};

#endif // MYTHREAD_H
