#ifndef TESTCRYPTODATA_H
#define TESTCRYPTODATA_H



#include <QObject>



class TestCryptoData : public QObject
{
    Q_OBJECT
public:
    TestCryptoData(QObject* parent = nullptr);


private slots:

    void initTestCase();


    void cleanupTestCase();

};

#endif // TESTCRYPTODATA_H
