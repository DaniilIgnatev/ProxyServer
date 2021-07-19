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

    if (!hasProxyPort()){
        message += "Settings are missing the " + key_proxyPort + "\n";
    }
    else{
        message += key_proxyPort + ": " + QString::number(proxyPort()) + "\n";
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
        message += key_shPort + ": " + QString::number(shPort()) + "\n";
    }

    if (!hasLogsPath()){
        message += "Settings are missing the " + key_logsPath + "\n";
    }
    else{
        message += key_logsPath + ": " + logsPath() + "\n";
    }

    message += key_logsEnabled + ": " + (logsEnabled() ? "true" : "false") + "\n";

    message += key_logSocketStatus + ": " + (logSocketStatus() ? "true" : "false") + "\n";

    message += key_logSocketContent + ": " + (logSocketContent() ? "true" : "false") + "\n";

    message = QDir::toNativeSeparators(message);
    return message;
}


bool Settings::initialized()
{
    return hasLogsPath() &&
           hasProxyPort() &&
           hasSHAdress() &&
           hasSHPort();
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


bool Settings::logSocketStatus()
{
    return this->_logSocketStatus;
}


bool Settings::logSocketContent()
{
    return this->_logSocketContent;
}


bool Settings::logsEnabled()
{
    return this->_logsEnabled;
}


Settings::Settings()
{

}


void Settings::read()
{
    QSettings ini(this->configPath(), QSettings::Format::IniFormat);

    this->_proxyPort = ini.value(key_proxyPort).toInt(&(this->_hasProxyPort));

    this->_shPort = ini.value(key_shPort).toInt(&(this->_hasSHPort));
    this->_shAdress = ini.value(key_shAdress, "localhost").toString();

    this->_logsPath = ini.value(key_logsPath).toString();
    this->_logsEnabled = ini.value(key_logsEnabled).toBool();

    this->_logSocketStatus = ini.value(key_logSocketStatus).toBool();
    this->_logSocketContent = ini.value(key_logSocketContent).toBool();
}
