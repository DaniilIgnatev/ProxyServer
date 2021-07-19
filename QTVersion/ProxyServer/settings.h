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


    QString configPath();


    QString diagnostics();


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
