#ifndef STORAGE_H
#define STORAGE_H



#include <QObject>
#include <QUuid>
#include <QMultiMap>
#include <QDateTime>
#include "request.h"
#include "stored_session.h"
#include <QMutex>


QMutex session_mutex;

QMultiMap<QDateTime,Stored_Session> session_map;


class Storage: QObject
{
    Q_OBJECT
public:

    explicit Storage(QObject *parent = nullptr);

    QString reserveUUID(SHCryptoHandshakeRequest request);
};

#endif // STORAGE_H
