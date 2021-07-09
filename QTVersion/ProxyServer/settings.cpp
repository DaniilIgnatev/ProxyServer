#include "settings.h"



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


Settings::Settings()
{

}


void Settings::read()
{
    QSettings ini(this->configPath, QSettings::Format::IniFormat);

    this->_proxyPort = ini.value(Settings::key_proxyPort).toInt(&(this->_hasProxyPort));
    this->_shPort = ini.value(Settings::key_shPort).toInt(&(this->_hasSHPort));
}
