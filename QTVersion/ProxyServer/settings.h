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


    bool _hasLogsEnabled = false;

    bool _logsEnabled = false;


    bool _hasLogSocketStatus = false;

    bool _logSocketStatus = false;


    bool _hasLogSocketContent = false;

    bool _logSocketContent = false;



public:

    Settings();


    const QString RootDirName = "SHProxyServer";


    const QString iniFileName = "config.ini";


    QString configPath();


    const QString key_proxyPort = "proxyport";


    int proxyPort();


    bool hasProxyPort();


    const QString key_shPort = "shport";


    int shPort();


    bool hasSHPort();


    const QString key_shAdress = "shadress";


    QString shAdress();


    bool hasSHAdress();


    const QString key_logsPath = "logspath";


    QString logsPath();


    bool hasLogsPath();


    const QString key_logsEnabled = "logsenabled";


    bool logsEnabled();


    const QString key_logSocketContent = "logsocketcontent";


    bool logSocketContent();


    const QString key_logSocketStatus = "logsocketstatus";


    bool logSocketStatus();



    QString diagnostics();


    bool initialized();


    void read();
};

#endif // SETTINGS_H
