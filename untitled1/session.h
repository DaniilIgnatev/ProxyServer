#ifndef SESSION_H
#define SESSION_H

#include <QTcpSocket>
#include <QThread>
#include "Protocol/protocolhandler.h"



class Session : public QThread
{
    Q_OBJECT
public:
    Session(quint16 socketDescriptor, QObject *parent = nullptr);

    ~Session();

    quint16 socketDescriptor;

    void send(QString &message);

private:
    QTcpSocket* socket = NULL;

    void run() override;

private slots:
    void readyRead();
    void socketClosed();
};


#endif // SESSION_H
