#include "log.h"



void Log::info(QByteArray message)
{
    qInfo("%s", qUtf8Printable(message));
}

void Log::debug(QByteArray message)
{
    qDebug("%s", qUtf8Printable(message));
}
