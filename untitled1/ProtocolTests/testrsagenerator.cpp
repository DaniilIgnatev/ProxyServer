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

}



void TestRSAGenerator::gcd()
{

}



void TestRSAGenerator::generatePublicExp()
{

}



void TestRSAGenerator::gcdExtend()
{

}



void TestRSAGenerator::gcdExtendReverse()
{

}
