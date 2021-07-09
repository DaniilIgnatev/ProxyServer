#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>
#include <QDir>


class Settings
{
private:

    bool _hasProxyPort = false;

    int _proxyPort = 8090;

    const QString key_proxyPort = "proxyport";


    bool _hasSHPort = false;

    int _shPort = 8084;

    const QString key_shPort = "shport";

public:

    const QString configPath = QDir::toNativeSeparators("C:/SHProxyServer/config.ini");


    int proxyPort();


    bool hasProxyPort();


    int shPort();


    bool hasSHPort();


    Settings();


    void read();
};

#endif // SETTINGS_H
