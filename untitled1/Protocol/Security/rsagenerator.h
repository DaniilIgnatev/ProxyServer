#ifndef RSAGENERATOR_H
#define RSAGENERATOR_H

#include <QObject>
#include <QList>
#include "securitykeyspair.h"
#include <QtMath>
#include <QRandomGenerator>



class RSAGenerator : public QObject
{
    Q_OBJECT
private:
    QRandomGenerator* randGener = QRandomGenerator::global();

public:

    explicit RSAGenerator(QObject *parent = nullptr);


    bool isPrime(int n);


    QList<int> generatePrimeNumbers(int start, int count);


    SecurityKeysPair testonlyGenerateSecurityKeys(int p, int q, int e);


    SecurityKeysPair generateSecurityKeys();


    int gcd(int a, int b);


    int generatePublicExp(int eiler);


    int gcdExtend(int a, int b, int &x, int &y);


    int gcdExtendReverse(int a, int b, int &x, int &y);
};

#endif // RSAGENERATOR_H
