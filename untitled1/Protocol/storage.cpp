#include "storage.h"
#include <QSqlDatabase>


Storage::Storage(QObject *parent): QObject(parent)
{

}


QString Storage::reserveUUID(SHCryptoHandshakeRequest request)
{
    QUuid newUUID = QUuid::createUuid();
    QString uuidStr = newUUID.toString();

    Stored_Session session(uuidStr,request.method,request.key);

    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QTime currentTime = currentDateTime.time();
    QTime resetTime = QTime(currentTime.hour(),0,0,0);
    currentDateTime.setTime(resetTime);

    session_mutex.lock();
    session_map.insert(currentDateTime, session);

    return uuidStr;
}
