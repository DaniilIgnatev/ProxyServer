#include "testrsagenerator.h"



TestRSAGenerator::TestRSAGenerator(QObject *parent) : QObject(parent)
{

}


void TestRSAGenerator::initTestCase()
{
    this->generator = new RSAGenerator(this);
}


void TestRSAGenerator::cleanupTestCase()
{

}


void TestRSAGenerator::isPrime()
{
    int primeTrue[] = {
        2, 3, 5, 7, 11, 13, 151, 157, 163, 199, 211, 223, 227, 229, 233, 239
    };

    for (int i = 0; i < (int)(sizeof(primeTrue)/sizeof(*primeTrue)); i++){
        bool isPrime = generator->isPrime(primeTrue[i]);
        QVERIFY(isPrime == true);
    }

    int primeFalse[] = {
        4, 6, 8, 12, 14, 152, 156, 162, 198, 210, 220, 225, 230, 235, 240
    };

    for (int i = 0; i < (int)(sizeof(primeFalse)/sizeof(*primeFalse)); i++){
        QVERIFY(!generator->isPrime(primeFalse[i]));
    }
}


void TestRSAGenerator::generatePrimeNumbers()
{
    const int generateBegin = 10;
    const int generateCount = 100000;

    auto primeNumbers = generator->generatePrimeNumbers(generateBegin,generateCount);
    for (int i = 0;i < primeNumbers.count(); i++){
        QVERIFY(generator->isPrime(primeNumbers[i]));
    }
    QVERIFY(primeNumbers.count() == generateCount);
}


void TestRSAGenerator::testonlyGenerateSecurityKeys()
{
    int p = 3557;
    int q = 2579;
    int e = 3;

    auto keys = generator->testonlyGenerateSecurityKeys(p, q, e);

    auto publicKeys = keys.publicKey;
    QCOMPARE(publicKeys.x, 3);
    QCOMPARE(publicKeys.y, 9173503);

    auto privateKeys = keys.privateKey;
    QCOMPARE(privateKeys.x, 6111579);
    QCOMPARE(privateKeys.y, 9173503);
}


void TestRSAGenerator::gcd()
{
    QCOMPARE(generator->gcd(23, 5), 1);
    QCOMPARE(generator->gcd(12, 664), 4);
    QCOMPARE(generator->gcd(15, 2), 1);
    QCOMPARE(generator->gcd(22, 2), 2);
    QCOMPARE(generator->gcd(27, 9), 9);
}


void TestRSAGenerator::gcdExtendReverse()
{
    QList<CryptoKey> GCD_One_Numbers = QList<CryptoKey>();

    while (GCD_One_Numbers.count() < 5) {
        int firstNum = randGener->bounded(1000);
        int firstPrime = generator->generatePrimeNumbers(firstNum, 1).first();

        int secondNum = randGener->bounded(1000);
        int secondPrime = generator->generatePrimeNumbers(secondNum, 1).first();

        int gcd = generator->gcd(firstPrime, secondPrime);
        if (gcd == 1){
            int x = 0;
            int y = 0;
            GCD_One_Numbers.append(CryptoKey(firstPrime,secondPrime));
            int d = generator->gcdExtendReverse(firstPrime, secondPrime, x, y);
            QCOMPARE(d, 1);
        }
    }

    int a = 3;
    int b = 9167368;
    int x = 0;
    int y = 0;
    int d = generator->gcdExtendReverse(a, b, x, y);
    QCOMPARE(d, 1);
    QCOMPARE(x, 6111579);
}
