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
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();
        QTime nowTime = nowDateTime.time();
        QString nowStr = QString::number(nowDate.day()) + "d_" + QString::number(nowDate.month()) + "m_" + QString::number(nowTime.hour()) + "h_" +QString::number(nowTime.minute()) + "m_" + QString::number(nowTime.second()) + "s_" + QString::number(nowTime.msec()) + "ms";
        QString logFilePath = logDirPath + "/" + nowStr;
        if (id != ""){
            logFilePath += "_" + id + "id";
        }
        logFilePath += ".txt";

        logFilePath = QDir::toNativeSeparators(logFilePath);
        logFile = new QFile(logFilePath);

        bool opened = logFile->open(QIODevice::WriteOnly | QIODevice::Text);
        if (!opened){
            qDebug() << "Error opening file " << logFilePath;
        }
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
