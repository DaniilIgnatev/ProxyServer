#ifndef RSAGENERATORSINGLETRON_H
#define RSAGENERATORSINGLETRON_H

#include <QObject>
#include <QList>
#include "cryptokeysdescriptor.h"
#include <QtMath>
#include <QRandomGenerator>
#include <QTimer>
#include "rsagenerator.h"
#include <QMutex>
#include <QtDebug>
#include <QMultiMap>


class RSAGeneratorSingletron: public QObject
{
    Q_OBJECT
private:

    QTimer *updateKeysTimer = nullptr;


    RSAGenerator *generator = nullptr;


    RSAGeneratorSingletron();


    ~RSAGeneratorSingletron();


    QMultiMap<CryptoKey,CryptoKeysDescriptor> clientToKeysMap;


    CryptoKeysDescriptor* keys = nullptr;

private slots:

    void regenerateKeys();


public:

    const CryptoKey _get_self_private_key(CryptoKey client_key);


    const CryptoKey _get_self_public_key(CryptoKey client_key);

//STATIC

private:

    static QMutex getInstanceMutex;


    static RSAGeneratorSingletron *instance;

public:

    static RSAGeneratorSingletron *getInstance();


    static const CryptoKey get_self_private_key(CryptoKey client_key);


    static const CryptoKey get_self_public_key(CryptoKey client_key);
};


#endif // RSAGENERATORSINGLETRON_H
