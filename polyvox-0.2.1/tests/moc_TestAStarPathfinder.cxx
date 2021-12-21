/****************************************************************************
** Meta object code from reading C++ file 'TestAStarPathfinder.h'
**
** Created: Sat Mar 2 22:13:15 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TestAStarPathfinder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestAStarPathfinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestAStarPathfinder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestAStarPathfinder[] = {
    "TestAStarPathfinder\0\0testExecute()\0"
};

void TestAStarPathfinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TestAStarPathfinder *_t = static_cast<TestAStarPathfinder *>(_o);
        switch (_id) {
        case 0: _t->testExecute(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TestAStarPathfinder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TestAStarPathfinder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestAStarPathfinder,
      qt_meta_data_TestAStarPathfinder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestAStarPathfinder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestAStarPathfinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestAStarPathfinder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestAStarPathfinder))
        return static_cast<void*>(const_cast< TestAStarPathfinder*>(this));
    return QObject::qt_metacast(_clname);
}

int TestAStarPathfinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
