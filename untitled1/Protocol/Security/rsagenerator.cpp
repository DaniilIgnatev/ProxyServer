#include "rsagenerator.h"



RSAGenerator::RSAGenerator(QObject *parent) : QObject(parent)
{

}


bool RSAGenerator::isPrime(int n)
{
    if (n == 2 || n == 3){
        return true;
    }
    else if (n <= 1 || (n % 2) == 0 || (n % 3) == 0){
        return false;
    }
    int i = 5;
    while (qPow(i,2) <= n) {
        if ((n % i) == 0 || (n % (i + 2)) == 0){
            return false;
        }
        i += 6;
    }

    return true;
}


QList<int> RSAGenerator::generatePrimeNumbers(int start, int count)
{
    int generated = 0;
    QList<int> result;
    int number = start;

    while (generated < count) {
        if (isPrime(number)){
            result.append(number);
            generated++;
        }

        number++;
    }

    return result;
}


SecurityKeysPair RSAGenerator::testonlyGenerateSecurityKeys(int p, int q, int e)
{

}


SecurityKeysPair RSAGenerator::generateSecurityKeys()
{

}


int RSAGenerator::gcd(int a, int b)
{

}


int RSAGenerator::generatePublicExp(int eiler)
{

}


int RSAGenerator::gcdExtend(int a, int b, int &x, int &y)
{

}


int RSAGenerator::gcdExtendReverse(int a, int b, int &x, int &y)
{

}
