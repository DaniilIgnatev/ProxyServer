#include "logwriter.h"



bool LogWriter::modeEnabled(LogWriter::LogWriterEnum mode)
{
    switch (mode) {
    case Protocol:
        return true;
    case Status:
        return this->statusEnabled;
    case Content:
        return this->contentEnabled;
    }
}


LogWriter::LogWriter(bool enabled, bool statusEnabled, bool contentEnabled, QString logDirPath, QString id, QObject *parent): QObject(parent)
{
    this->enabled = enabled;
    this->statusEnabled = statusEnabled;
    this->contentEnabled = contentEnabled;

    logDir = new QDir(logDirPath);

    if (enabled){
        QString nowStr = QDateTime::currentDateTime().toString(Qt::DateFormat::DefaultLocaleLongDate);
        QString logFilePath = logDirPath + "/" + nowStr;
        if (id != ""){
            logFilePath += "_" + id;
        }
        logFilePath += ".txt";

        logFile = new QFile(logFilePath);
        logFile->open(QFile::WriteOnly);
    }
}


LogWriter::~LogWriter(){
    if (enabled){
        logFile->waitForBytesWritten(WAIT_FOR_BYTES_WRITTEN_MS);
        logFile->close();
        logFile->deleteLater();
    }

    if (logDir != nullptr){
        delete logDir;
        logDir = nullptr;
    }
}


void LogWriter::log(QByteArray &message, LogWriterEnum mode, bool file)
{
    if (enabled && modeEnabled(mode)){
        qDebug() << message;
        if (file){
            logFile->write(message);
        }
    }
}


void LogWriter::log(const char message[], LogWriterEnum mode, bool file)
{
    if (enabled && modeEnabled(mode)){
        qDebug() << message;
        if (file){
            logFile->write(message);
        }
    }
}


void LogWriter::log(QByteArray *message, LogWriterEnum mode, bool file)
{
    if (enabled && modeEnabled(mode)){
        qDebug() << *message;
        if (file){
            logFile->write(*message);
        }
    }
}
