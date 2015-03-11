/****************************************************************************
** Meta object code from reading C++ file 'amyVariableArea.h'
**
** Created: Wed Mar 11 01:25:44 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyVariableArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyVariableArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyVariableArea[] = {

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
      17,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyVariableArea[] = {
    "amyVariableArea\0\0DeleteSelected()\0"
};

void amyVariableArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyVariableArea *_t = static_cast<amyVariableArea *>(_o);
        switch (_id) {
        case 0: _t->DeleteSelected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyVariableArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyVariableArea::staticMetaObject = {
    { &amyCanvas::staticMetaObject, qt_meta_stringdata_amyVariableArea,
      qt_meta_data_amyVariableArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyVariableArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyVariableArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyVariableArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyVariableArea))
        return static_cast<void*>(const_cast< amyVariableArea*>(this));
    return amyCanvas::qt_metacast(_clname);
}

int amyVariableArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyCanvas::qt_metacall(_c, _id, _a);
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
