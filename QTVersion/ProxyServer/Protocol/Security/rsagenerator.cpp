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


CryptoKeysDescriptor RSAGenerator::testonlyGenerateSecurityKeys(int p, int q, int e)
{
    int n = p * q;
    int eiler = (p - 1) * (q - 1);

    int d= 0;
    int y = 0;
    gcdExtendReverse(e,eiler,d,y);

    return CryptoKeysDescriptor(CryptoKey(e,n),CryptoKey(d,n));
}


CryptoKeysDescriptor RSAGenerator::generateSecurityKeys()
{
    int p_base = QRandomGenerator::global()->bounded(3,50);
    auto p_primeList = generatePrimeNumbers(p_base,1);
    int p = p_primeList.first();

    int q_base = QRandomGenerator::global()->bounded(51,100);
    auto q_primeList = generatePrimeNumbers(q_base,1);
    int q = q_primeList.first();

    int n = p * q;
    int eiler = (p - 1) * (q - 1);

    int e = generatePublicExp(eiler);
    int d = 0;
    int y = 0;
    gcdExtendReverse(e,eiler,d,y);

    return CryptoKeysDescriptor(CryptoKey(e,n), CryptoKey(d,n));
}


int RSAGenerator::gcd(int a, int b)
{
    int remainder = abs(a) % abs(b);

    if (remainder != 0){
        return gcd(abs(b),remainder);
    }
    else{
        return abs(b);
    }
}


int RSAGenerator::generatePublicExp(int eiler)
{
    int result = QRandomGenerator::global()->bounded(3,eiler / 2);
    while (gcd(result,eiler) != 1) {
        result += 1;
    }

    return result;
}


int RSAGenerator::gcdExtend(int a, int b, int &x, int &y)
{
    if (a == 0){
        x = 0;
        y = 1;
        return b;
    }

    int x1 = 0;
    int y1 = 0;
    int gcd = gcdExtend(b % a,a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}


int RSAGenerator::gcdExtendReverse(int a, int b, int &x, int &y)
{
    int gcd = gcdExtend(a,b,x,y);

    if (x < 0){
        x = abs(x);
        x = b - x;
    }

    return gcd;
}
