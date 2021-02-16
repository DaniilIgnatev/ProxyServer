#ifndef LOG_H
#define LOG_H



#include <QByteArray>
#include <QtDebug>



class Log
{
public:
    static void info(QByteArray message);

    static void debug(QByteArray message);
};

#endif // LOG_H
