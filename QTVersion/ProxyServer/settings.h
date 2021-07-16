#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>
#include <QDir>
#include <QSysInfo>
#include <QStandardPaths>
#include <QDebug>


class Settings
{
private:

    bool _hasProxyPort = false;

    int _proxyPort = 8090;


    bool _hasSHPort = false;

    int _shPort = 8084;


    QString _shAdress = "localhost";


    QString _logsPath = "";

public:

    const QString key_proxyPort = "proxyport";

    const QString key_shPort = "shport";

    const QString key_shAdress = "shadress";

    const QString key_logsPath = "logspath";

    const QString RootDirName = "SHProxyServer";

    const QString iniFileName = "config.ini";

    QString configPath(){
        auto kernal = QSysInfo::kernelType();
        if (kernal == "winnt"){
            return QDir::toNativeSeparators("C:/" + RootDirName + "/" + iniFileName);
        }
        else{
            QString homePath = QDir::homePath();
            return QDir::toNativeSeparators(homePath + "/" +  RootDirName + "/" + iniFileName);
        }
    }


    QString diagnostics(){
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


    bool initialized();


    int proxyPort();


    bool hasProxyPort();


    int shPort();


    bool hasSHPort();


    QString shAdress();


    bool hasSHAdress();


    QString logsPath();


    bool hasLogsPath();


    Settings();


    void read();
};

#endif // SETTINGS_H
