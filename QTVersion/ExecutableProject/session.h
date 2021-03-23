#ifndef SESSION_H
#define SESSION_H



#include <QTcpSocket>
#include <QThread>
#include <QDataStream>
#include "Protocol/protocolhandler.h"
#include <QtDebug>


/*
Session содержит protocolhandler
Session Посылает сигнал, о поступлении запроса
protocolhandler посылает сигнал о поступлении ответа
*/

///Предоставляет внешний интерфейс для клиента
class Session : public QObject
{
    Q_OBJECT
public:
    Session(quint16 socketDescriptor);

    ~Session();

    quint16 socketDescriptor;

    void send(QString &message);

signals:
    void requestReady(QByteArray &request);

public slots:
    void handleResponse(QByteArray  &response);

private:

    QThread *thread;

    ProtocolHandler *protocolHandler;

    QTcpSocket* socket;

    ///Всего для чтения
    quint32 request_size = 0;

    ///Уже прочитано
    quint32 bytes_read = 0;

    QByteArray* readData = NULL;

    QDataStream* readStream = NULL;

    qint32 response_size = 0;

private slots:
    void readyRead();
    void socketClosed();
};


#endif // SESSION_H 
