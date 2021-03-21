#ifndef TESTRSACRYPTOPROXY_H
#define TESTRSACRYPTOPROXY_H

#include <QObject>
#include <QString>
#include <QtTest>
#include "../ExecutableProject/Protocol/Security/cryptokeysdescriptor.h"
#include "../ExecutableProject/Protocol/Security/rsacryptoproxy.h"



class TestRSACryptoProxy : public QObject
{
    Q_OBJECT
private:

    RSACryptoProxy *cryptoProxy = nullptr;

public:
    explicit TestRSACryptoProxy(QObject *parent = nullptr);

private slots:

    void initTestCase();


    void cleanupTestCase();


    void encryptDecrypt();
};

#endif // TESTRSACRYPTOPROXY_H
