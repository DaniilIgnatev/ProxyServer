#ifndef SESSION_H
#define SESSION_H



#include <QTcpSocket>
#include <QThread>
#include <QDataStream>
#include "Protocol/protocolhandler.h"
#include <QtDebug>
#include "log.h"


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
    void requestReady(QByteArray* request);

public slots:
    void handleResponse(QByteArray* response);

private:
    void run() override;

    ProtocolHandler *protocol = NULL;

    QTcpSocket* socket = NULL;

    uint32_t request_size = 0;

    uint32_t bytes_read = 0;

    QByteArray* readData = NULL;

    QDataStream* readStream = NULL;

private slots:
    void readyRead();
    void socketClosed();
};


#endif // SESSION_H
