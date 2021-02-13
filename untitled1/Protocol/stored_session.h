#ifndef STORED_SESSION_H
#define STORED_SESSION_H

#include <QObject>


class Stored_Session : public QObject
{
    Q_OBJECT
public:
    QString uuid;

    int method;

    QString key;

    void read(const QJsonObject &json);

    void write(const QJsonObject &json);
};

#endif // STORED_SESSION_H


