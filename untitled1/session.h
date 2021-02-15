#ifndef SESSION_H
#define SESSION_H



#include <QTcpSocket>
#include <QThread>
#include "Protocol/protocolhandler.h"
#include <QtDebug>


/*
Session содержит protocolhandler
Session Посылает сигнал, о поступлении запроса
protocolhandler посылает сигнал о поступлении ответа
*/

///Предоставляет внешний интерфейс для клиента
class Session : public QThread
{
    Q_OBJECT
public:
    Session(quint16 socketDescriptor, QObject *parent = nullptr);

    ~Session();

    quint16 socketDescriptor;

    void send(QString &message);

signals:
    void requestReady(QByteArray request);

public slots:
    void handleResponse(QByteArray response);

private:
    QTcpSocket* socket = NULL;

    ProtocolHandler* protocol = NULL;

    void run() override;

private slots:
    void readyRead();
    void socketClosed();
};


#endif // SESSION_H
