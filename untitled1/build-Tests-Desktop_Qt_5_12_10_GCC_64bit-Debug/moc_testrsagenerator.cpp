/****************************************************************************
** Meta object code from reading C++ file 'testrsagenerator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Tests/testrsagenerator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testrsagenerator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestRSAGenerator_t {
    QByteArrayData data[9];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestRSAGenerator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestRSAGenerator_t qt_meta_stringdata_TestRSAGenerator = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TestRSAGenerator"
QT_MOC_LITERAL(1, 17, 7), // "isPrime"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "generatePrimeNumbers"
QT_MOC_LITERAL(4, 47, 28), // "testonlyGenerateSecurityKeys"
QT_MOC_LITERAL(5, 76, 3), // "gcd"
QT_MOC_LITERAL(6, 80, 17), // "generatePublicExp"
QT_MOC_LITERAL(7, 98, 9), // "gcdExtend"
QT_MOC_LITERAL(8, 108, 16) // "gcdExtendReverse"

    },
    "TestRSAGenerator\0isPrime\0\0"
    "generatePrimeNumbers\0testonlyGenerateSecurityKeys\0"
    "gcd\0generatePublicExp\0gcdExtend\0"
    "gcdExtendReverse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestRSAGenerator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TestRSAGenerator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestRSAGenerator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isPrime(); break;
        case 1: _t->generatePrimeNumbers(); break;
        case 2: _t->testonlyGenerateSecurityKeys(); break;
        case 3: _t->gcd(); break;
        case 4: _t->generatePublicExp(); break;
        case 5: _t->gcdExtend(); break;
        case 6: _t->gcdExtendReverse(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TestRSAGenerator::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TestRSAGenerator.data,
    qt_meta_data_TestRSAGenerator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestRSAGenerator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestRSAGenerator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestRSAGenerator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TestRSAGenerator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
