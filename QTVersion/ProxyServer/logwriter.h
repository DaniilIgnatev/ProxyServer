#ifndef LOGWRITER_H
#define LOGWRITER_H



#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>



class LogWriter : public QObject
{
    Q_OBJECT
private:
    QDir* logDir = nullptr;

    QFile* logFile = nullptr;

public:

    explicit LogWriter(QString logDirPath, QString id = QString(), QObject *parent = nullptr);


    ~LogWriter();


    void log(QByteArray &message, bool file = true);


    void log (const char message[], bool file = true);


    void log(QByteArray *message, bool file = true);

signals:

};

#endif // LOGWRITER_H
