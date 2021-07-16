#include "logwriter.h"



LogWriter::LogWriter(QString logDirPath, QString id, QObject *parent): QObject(parent)
{
    logDir = new QDir(logDirPath);

    QString nowStr = QDateTime::currentDateTime().toString(Qt::DateFormat::DefaultLocaleLongDate);
    QString logFilePath = logDirPath + "/" + nowStr;
    if (id != ""){
        logFilePath += "_" + id;
    }
    logFilePath += ".txt";

    logFile = new QFile(logFilePath);
    logFile->open(QFile::WriteOnly);
}


LogWriter::~LogWriter(){
    logFile->close();
    delete logFile;
    delete logDir;
}


void LogWriter::log(QByteArray &message, bool file)
{
    qDebug() << message;
    if (file){
        logFile->write(message);
    }
}


void LogWriter::log(const char message[], bool file)
{
    qDebug() << message;
    if (file){
        logFile->write(message);
    }
}


void LogWriter::log(QByteArray *message, bool file)
{
    qDebug() << message;
    if (file){
        logFile->write(message->data());
    }
}
