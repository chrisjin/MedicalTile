/****************************************************************************
** Meta object code from reading C++ file 'amyAlgorithmRunner.h'
**
** Created: Wed Mar 11 01:25:33 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyAlgorithmRunner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyAlgorithmRunner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyAlgorithmRunner[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      36,   19,   19,   19, 0x05,
      50,   19,   19,   19, 0x05,
      64,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyAlgorithmRunner[] = {
    "amyAlgorithmRunner\0\0s_begin_check()\0"
    "s_end_check()\0s_begin_run()\0s_end_run()\0"
};

void amyAlgorithmRunner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyAlgorithmRunner *_t = static_cast<amyAlgorithmRunner *>(_o);
        switch (_id) {
        case 0: _t->s_begin_check(); break;
        case 1: _t->s_end_check(); break;
        case 2: _t->s_begin_run(); break;
        case 3: _t->s_end_run(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyAlgorithmRunner::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAlgorithmRunner::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyAlgorithmRunner,
      qt_meta_data_amyAlgorithmRunner, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAlgorithmRunner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAlgorithmRunner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAlgorithmRunner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAlgorithmRunner))
        return static_cast<void*>(const_cast< amyAlgorithmRunner*>(this));
    return QObject::qt_metacast(_clname);
}

int amyAlgorithmRunner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void amyAlgorithmRunner::s_begin_check()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void amyAlgorithmRunner::s_end_check()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void amyAlgorithmRunner::s_begin_run()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void amyAlgorithmRunner::s_end_run()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
