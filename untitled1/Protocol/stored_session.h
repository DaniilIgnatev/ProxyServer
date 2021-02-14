#ifndef STORED_SESSION_H
#define STORED_SESSION_H

#include <QObject>
#include <QString>
#include <QJsonObject>


struct Stored_Session
{
    QString uuid;

    int method;

    QString key;

    Stored_Session(QString uuid, int method, QString key);

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // STORED_SESSION_H


