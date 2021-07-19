#include "settings.h"



QString Settings::configPath()
{
    auto kernal = QSysInfo::kernelType();
    if (kernal == "winnt"){
        return QDir::toNativeSeparators("C:/" + RootDirName + "/" + iniFileName);
    }
    else{
        QString homePath = QDir::homePath();
        return QDir::toNativeSeparators(homePath + "/" +  this->RootDirName + "/" + this->iniFileName);
    }
}


QString Settings::diagnostics()
{
    QString message = "";

    if (!hasLogsPath()){
        message += "Settings are missing the " + key_logsPath + "\n";
    }
    else{
        message += key_logsPath + ": " + logsPath() + "\n";
    }

    if (!hasProxyPort()){
        message += "Settings are missing the " + key_proxyPort + "\n";
    }
    else{
        message += key_proxyPort + ": " + proxyPort() + "\n";
    }

    if (!hasSHAdress()){
        message += "Settings are missing the " + key_shAdress + "\n";
    }
    else{
        message += key_shAdress + ": " + shAdress() + "\n";
    }

    if (!hasSHPort()){
        message += "Settings are missing the " + key_shPort + "\n";
    }
    else{
        message += key_shPort + ": " + shPort() + "\n";
    }

    message = QDir::toNativeSeparators(message);
    return message;
}


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

    QString defaultStr = "";

    this->_logsPath = ini.value(key_logsPath, defaultStr).toString();
    this->_proxyPort = ini.value(key_proxyPort).toInt(&(this->_hasProxyPort));
    this->_shPort = ini.value(key_shPort).toInt(&(this->_hasSHPort));
    this->_shAdress = ini.value(key_shAdress, defaultStr).toString();
}
