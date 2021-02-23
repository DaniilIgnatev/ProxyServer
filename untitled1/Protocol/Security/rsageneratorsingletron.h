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



class RSAGeneratorSingletron
{
private:

    QTimer *updateKeysTimer = nullptr;


    RSAGenerator *generator = nullptr;


    RSAGeneratorSingletron();


    CryptoKey self_private_key;


    CryptoKey self_public_key;


    CryptoKey past_private_key;


    CryptoKey past_public_key;

private slots:

    void updateKeys();


public:

    const CryptoKey _get_self_private_key();


    const CryptoKey _get_self_public_key();


    bool _hasPastKey();


    const CryptoKey _get_past_private_key();


    const CryptoKey _get_past_public_key();

//STATIC

private:

    static QMutex getInstanceMutex;


    static RSAGeneratorSingletron *instance;

public:

    static RSAGeneratorSingletron *getInstance();


    static const CryptoKey get_self_private_key();


    static const CryptoKey get_self_public_key();


    static bool hasPastKey();


    static const CryptoKey get_past_private_key();


    static const CryptoKey get_past_public_key();
};


#endif // RSAGENERATORSINGLETRON_H
