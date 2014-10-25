/****************************************************************************
** Meta object code from reading C++ file 'amyAlgorithmManager.h'
**
** Created: Fri Mar 21 11:15:00 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyAlgorithmManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyAlgorithmManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyAlgorithmQ[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      28,   14,   14,   14, 0x05,
      42,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyAlgorithmQ[] = {
    "amyAlgorithmQ\0\0s_retrieve()\0s_taskstart()\0"
    "s_taskover()\0Retrieve()\0"
};

void amyAlgorithmQ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyAlgorithmQ *_t = static_cast<amyAlgorithmQ *>(_o);
        switch (_id) {
        case 0: _t->s_retrieve(); break;
        case 1: _t->s_taskstart(); break;
        case 2: _t->s_taskover(); break;
        case 3: _t->Retrieve(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyAlgorithmQ::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAlgorithmQ::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyAlgorithmQ,
      qt_meta_data_amyAlgorithmQ, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAlgorithmQ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAlgorithmQ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAlgorithmQ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAlgorithmQ))
        return static_cast<void*>(const_cast< amyAlgorithmQ*>(this));
    return QObject::qt_metacast(_clname);
}

int amyAlgorithmQ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void amyAlgorithmQ::s_retrieve()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void amyAlgorithmQ::s_taskstart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void amyAlgorithmQ::s_taskover()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_amyAlgorithmManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyAlgorithmManager[] = {
    "amyAlgorithmManager\0\0"
    "s_algorithmchoose(amyAlgorithm*)\0"
    "SendRetrieveSig()\0"
};

void amyAlgorithmManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyAlgorithmManager *_t = static_cast<amyAlgorithmManager *>(_o);
        switch (_id) {
        case 0: _t->s_algorithmchoose((*reinterpret_cast< amyAlgorithm*(*)>(_a[1]))); break;
        case 1: _t->SendRetrieveSig(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyAlgorithmManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAlgorithmManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyAlgorithmManager,
      qt_meta_data_amyAlgorithmManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAlgorithmManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAlgorithmManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAlgorithmManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAlgorithmManager))
        return static_cast<void*>(const_cast< amyAlgorithmManager*>(this));
    return QObject::qt_metacast(_clname);
}

int amyAlgorithmManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void amyAlgorithmManager::s_algorithmchoose(amyAlgorithm * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
