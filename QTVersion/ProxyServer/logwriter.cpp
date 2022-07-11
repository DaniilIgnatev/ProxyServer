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


LogWriter::LogWriter(bool enabled, bool statusEnabled, bool contentEnabled, QString logRootDirPath, QString id, QObject *parent): QObject(parent)
{
    this->enabled = enabled;
    this->statusEnabled = statusEnabled;
    this->contentEnabled = contentEnabled;

    logDir = new QDir(logRootDirPath);

    if (enabled){
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();
        QTime nowTime = nowDateTime.time();

        //формат папки-даты 2022-07-11
        QString nowDateStr = QString::number(nowDate.year()) + "-" + QString::number(nowDate.month()) + "-" + QString::number(nowDate.day());
        QString logDirPath = logRootDirPath + "/" + nowDateStr;

        //формат файла-времени 13-56-38_2508
        QString nowTimeStr = QString::number(nowTime.hour()) + "-" +QString::number(nowTime.minute()) + "-" + QString::number(nowTime.second()) + "_" + QString::number(nowTime.msec());
        QString logFilePath = logDirPath + "/" + nowTimeStr;

        if (id != ""){
            logFilePath += " " + id;
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
