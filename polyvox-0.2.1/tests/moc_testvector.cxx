/****************************************************************************
** Meta object code from reading C++ file 'testvector.h'
**
** Created: Sat Mar 2 22:13:21 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testvector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testvector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestVector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      25,   11,   11,   11, 0x08,
      42,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestVector[] = {
    "TestVector\0\0testLength()\0testDotProduct()\0"
    "testEquality()\0"
};

void TestVector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TestVector *_t = static_cast<TestVector *>(_o);
        switch (_id) {
        case 0: _t->testLength(); break;
        case 1: _t->testDotProduct(); break;
        case 2: _t->testEquality(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TestVector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TestVector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestVector,
      qt_meta_data_TestVector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestVector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestVector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestVector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestVector))
        return static_cast<void*>(const_cast< TestVector*>(this));
    return QObject::qt_metacast(_clname);
}

int TestVector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
