#include "settings.h"



bool Settings::initialized()
{
    return hasLogsPath() && hasProxyPort() && hasSHAdress() && hasSHPort();
}


int Settings::proxyPort()
{
    return _proxyPort;
}


bool Settings::hasProxyPort()
{
    return _hasProxyPort;
}


int Settings::shPort()
{
    return _shPort;
}


bool Settings::hasSHPort()
{
    return _hasSHPort;
}


QString Settings::shAdress()
{
    return this->_shAdress;
}


bool Settings::hasSHAdress()
{
    return this->_shAdress != "";
}


QString Settings::logsPath()
{
    return this->_logsPath;
}


bool Settings::hasLogsPath()
{
    return this->_logsPath != "";
}


Settings::Settings()
{

}


void Settings::read()
{
    QSettings ini(this->configPath(), QSettings::Format::IniFormat);

    this->_logsPath = ini.value(Settings::key_logsPath).toString();
    this->_proxyPort = ini.value(Settings::key_proxyPort).toInt(&(this->_hasProxyPort));
    this->_shPort = ini.value(Settings::key_shPort).toInt(&(this->_hasSHPort));
    this->_shAdress = ini.value(Settings::key_shAdress).toString();
}
