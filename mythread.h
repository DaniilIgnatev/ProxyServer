#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QtDebug>
#include <QTcpSocket>

class MyThread : public QThread
{
   Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    void run() override;

signals:
    void error (QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // MYTHREAD_H
