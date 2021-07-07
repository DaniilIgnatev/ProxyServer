#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>


class Settings
{
private:

    bool _hasPort = false;

    int _port = 8090;

    const QString key_port = "port";

public:

    int port();


    bool hasPort();


    Settings();


    void read();
};

#endif // SETTINGS_H
