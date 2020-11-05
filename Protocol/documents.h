#ifndef DOCUMENT_H
#define DOCUMENT_H

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

#endif // DOCUMENT_H
