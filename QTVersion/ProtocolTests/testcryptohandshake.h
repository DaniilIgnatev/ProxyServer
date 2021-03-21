#ifndef TESTHANDSHAKE_H
#define TESTHANDSHAKE_H


#include <QtTest>
#include <QObject>


class TestCryptoHandshake : public QObject
{
    Q_OBJECT
public:
    explicit TestCryptoHandshake(QObject *parent = nullptr);

private slots:

    void initTestCase();


    void cleanupTestCase();


    void testHandshake();
};

#endif // TESTHANDSHAKE_H
