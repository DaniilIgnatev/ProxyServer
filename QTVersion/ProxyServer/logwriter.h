#ifndef LOGWRITER_H
#define LOGWRITER_H



#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>



#define WAIT_FOR_BYTES_WRITTEN_MS 5000





class LogWriter : public QObject
{
    Q_OBJECT
private:
    QDir* logDir = nullptr;

    QFile* logFile = nullptr;

    bool enabled = false;

    bool statusEnabled = false;

    bool contentEnabled = false;

public:
    enum LogWriterEnum{
        Protocol,
        Status,
        Content
    };
    Q_ENUM(LogWriterEnum);

private:

    bool modeEnabled(LogWriterEnum mode);

public:

    explicit LogWriter(bool enabled, bool statusEnabled, bool contentEnabled, QString logDirPath, QString id = QString(), QObject *parent = nullptr);


    ~LogWriter();


    void log(QByteArray &message, LogWriterEnum mode, bool file = true);


    void log (const char message[], LogWriterEnum mode, bool file = true);


    void log(QByteArray *message, LogWriterEnum mode, bool file = true);

signals:

};

#endif // LOGWRITER_H
