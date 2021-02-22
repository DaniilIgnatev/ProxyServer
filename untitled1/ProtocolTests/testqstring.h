#ifndef TESTQSTRING_H
#define TESTQSTRING_H

#include <QObject>
#include <QString>
#include <QtTest/QTest>


class TestQString : public QObject
{
    Q_OBJECT
public:
    explicit TestQString(QObject *parent = nullptr);

private slots:
    void toUpper();
};

#endif // TESTQSTRING_H
