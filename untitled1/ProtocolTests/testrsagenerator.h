#ifndef TESTRSAGENERATOR_H
#define TESTRSAGENERATOR_H

#include <QObject>
#include <QTest>
#include <QList>
#include "../Protocol/Security/securitykeyspair.h"
#include "../Protocol/Security/rsagenerator.h"
#include <QRandomGenerator>



class TestRSAGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TestRSAGenerator(QObject *parent = nullptr);

private:
    RSAGenerator *generator = nullptr;

    QRandomGenerator* randGener = QRandomGenerator::global();

private slots:

    void initTestCase();


    void cleanupTestCase();


    void isPrime();


    void generatePrimeNumbers();


    void testonlyGenerateSecurityKeys();


    void gcd();


    void gcdExtendReverse();
};

#endif // TESTRSAGENERATOR_H
