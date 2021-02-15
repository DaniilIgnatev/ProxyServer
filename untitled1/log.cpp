#include "log.h"



void Log::info(QByteArray message)
{
    qInfo("%s", qUtf8Printable(message));
}
