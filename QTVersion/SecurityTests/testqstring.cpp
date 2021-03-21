#include "testqstring.h"



TestQString::TestQString(QObject *parent) : QObject(parent)
{

}

void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(),"HELLO");
}
