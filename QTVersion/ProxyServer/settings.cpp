#include "settings.h"



int Settings::port()
{
    return _port;
}


bool Settings::hasPort()
{
    return _hasPort;
}


Settings::Settings()
{

}


void Settings::read()
{
    QSettings ini("config.ini",QSettings::Format::IniFormat);

    this->_port = ini.value(Settings::key_port).toInt(&(this->_hasPort));
}
