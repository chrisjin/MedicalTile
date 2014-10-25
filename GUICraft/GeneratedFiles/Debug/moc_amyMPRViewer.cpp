/****************************************************************************
** Meta object code from reading C++ file 'amyMPRViewer.h'
**
** Created: Sun Mar 23 18:56:55 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyMPRViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyMPRViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyMPRViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      23,   13,   13,   13, 0x0a,
      44,   13,   13,   13, 0x0a,
      63,   13,   13,   13, 0x0a,
      86,   13,   13,   13, 0x0a,
     107,   13,   13,   13, 0x0a,
     131,   13,   13,   13, 0x0a,
     153,   13,   13,   13, 0x0a,
     177,   13,   13,   13, 0x0a,
     199,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyMPRViewer[] = {
    "amyMPRViewer\0\0OnDrop()\0AxialHorizontal(int)\0"
    "AxialVertical(int)\0CoronalHorizontal(int)\0"
    "CoronalVertical(int)\0SagittalHorizontal(int)\0"
    "SagittalVertical(int)\0CoronalSliceChange(int)\0"
    "AxialSliceChange(int)\0SagittalSliceChange(int)\0"
};

void amyMPRViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyMPRViewer *_t = static_cast<amyMPRViewer *>(_o);
        switch (_id) {
        case 0: _t->OnDrop(); break;
        case 1: _t->AxialHorizontal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->AxialVertical((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->CoronalHorizontal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->CoronalVertical((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SagittalHorizontal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SagittalVertical((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->CoronalSliceChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->AxialSliceChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SagittalSliceChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyMPRViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyMPRViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amyMPRViewer,
      qt_meta_data_amyMPRViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyMPRViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyMPRViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyMPRViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyMPRViewer))
        return static_cast<void*>(const_cast< amyMPRViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int amyMPRViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
