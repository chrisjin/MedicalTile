/****************************************************************************
** Meta object code from reading C++ file 'amyAnnotationLing.h'
**
** Created: Wed Mar 11 01:25:43 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyAnnotationLing.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyAnnotationLing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyAnnotationLing[] = {

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
      23,   19,   18,   18, 0x0a,
      48,   42,   18,   18, 0x0a,
      62,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyAnnotationLing[] = {
    "amyAnnotationLing\0\0c,w\0SetWindow(int,int)\0"
    "index\0SetSlice(int)\0SetCubeLingInput()\0"
};

void amyAnnotationLing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyAnnotationLing *_t = static_cast<amyAnnotationLing *>(_o);
        switch (_id) {
        case 0: _t->SetWindow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SetSlice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SetCubeLingInput(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyAnnotationLing::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAnnotationLing::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyAnnotationLing,
      qt_meta_data_amyAnnotationLing, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAnnotationLing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAnnotationLing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAnnotationLing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAnnotationLing))
        return static_cast<void*>(const_cast< amyAnnotationLing*>(this));
    if (!strcmp(_clname, "amyLing"))
        return static_cast< amyLing*>(const_cast< amyAnnotationLing*>(this));
    return QObject::qt_metacast(_clname);
}

int amyAnnotationLing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
