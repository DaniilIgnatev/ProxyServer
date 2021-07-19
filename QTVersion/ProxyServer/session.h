#ifndef SESSION_H
#define SESSION_H



#include <QTcpSocket>
#include <QThread>
#include <QDataStream>
#include "Protocol/protocolhandler.h"
#include <QtDebug>
#include "json_extension.h"
#include <QFile>
#include "settings.h"
#include "logwriter.h"


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
    Session(quint16 socketDescriptor, Settings* settings);


    ~Session();


    quint16 socketDescriptor;


signals:
    void requestReady(QByteArray &request);


public slots:
    void handleResponse(QByteArray  &response);


private:

    Settings *settings = nullptr;


    LogWriter *logWriter = nullptr;


    QThread *thread = nullptr;


    ProtocolHandler *protocolHandler = nullptr;


    QTcpSocket* socket = nullptr;


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
