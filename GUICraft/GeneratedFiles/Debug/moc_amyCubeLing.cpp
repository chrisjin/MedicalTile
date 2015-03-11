/****************************************************************************
** Meta object code from reading C++ file 'amyCubeLing.h'
**
** Created: Wed Mar 11 01:25:44 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyCubeLing.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyCubeLing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyCubeLing[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      33,   12,   12,   12, 0x05,
      54,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyCubeLing[] = {
    "amyCubeLing\0\0s_slicechanged(int)\0"
    "s_slicechanging(int)\0s_inputchanged()\0"
};

void amyCubeLing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyCubeLing *_t = static_cast<amyCubeLing *>(_o);
        switch (_id) {
        case 0: _t->s_slicechanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->s_slicechanging((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->s_inputchanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyCubeLing::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyCubeLing::staticMetaObject = {
    { &amyZoomLing::staticMetaObject, qt_meta_stringdata_amyCubeLing,
      qt_meta_data_amyCubeLing, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyCubeLing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyCubeLing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyCubeLing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyCubeLing))
        return static_cast<void*>(const_cast< amyCubeLing*>(this));
    return amyZoomLing::qt_metacast(_clname);
}

int amyCubeLing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyZoomLing::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void amyCubeLing::s_slicechanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void amyCubeLing::s_slicechanging(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void amyCubeLing::s_inputchanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
