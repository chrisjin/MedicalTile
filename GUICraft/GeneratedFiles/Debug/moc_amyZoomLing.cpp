/****************************************************************************
** Meta object code from reading C++ file 'amyZoomLing.h'
**
** Created: Sun Mar 23 15:22:10 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyZoomLing.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyZoomLing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyZoomLing[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      43,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyZoomLing[] = {
    "amyZoomLing\0\0s_srcregiontranslated(QPoint)\0"
    "s_srcregionzoomed(int)\0"
};

void amyZoomLing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyZoomLing *_t = static_cast<amyZoomLing *>(_o);
        switch (_id) {
        case 0: _t->s_srcregiontranslated((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->s_srcregionzoomed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyZoomLing::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyZoomLing::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyZoomLing,
      qt_meta_data_amyZoomLing, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyZoomLing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyZoomLing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyZoomLing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyZoomLing))
        return static_cast<void*>(const_cast< amyZoomLing*>(this));
    if (!strcmp(_clname, "amyImageLing"))
        return static_cast< amyImageLing*>(const_cast< amyZoomLing*>(this));
    if (!strcmp(_clname, "amyInput<amyCube*>"))
        return static_cast< amyInput<amyCube*>*>(const_cast< amyZoomLing*>(this));
    return QObject::qt_metacast(_clname);
}

int amyZoomLing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void amyZoomLing::s_srcregiontranslated(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void amyZoomLing::s_srcregionzoomed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
