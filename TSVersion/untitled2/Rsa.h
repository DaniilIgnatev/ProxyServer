#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct key
{
  int x;
  int y;
};
struct table
{
  string value;
  string car;
};

void loadAscii();
key getPublicKey();
key getPrivateKey();
string enCrypt(string, key);
string deCrypt(string,key);
string toHex(string);
string toChar(string);
string numToHex(int);
string Reverse(string);
double powBig(double, int, int);
double toNum(string);

#endif // RSA_H
