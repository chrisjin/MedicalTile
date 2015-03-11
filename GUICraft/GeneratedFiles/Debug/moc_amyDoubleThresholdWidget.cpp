/****************************************************************************
** Meta object code from reading C++ file 'amyDoubleThresholdWidget.h'
**
** Created: Wed Mar 11 01:25:41 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyDoubleThresholdWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyDoubleThresholdWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyDoubleThresholdWidget[] = {

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
      28,   26,   25,   25, 0x05,
      61,   26,   25,   25, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyDoubleThresholdWidget[] = {
    "amyDoubleThresholdWidget\0\0,\0"
    "s_thresholdchanging(float,float)\0"
    "s_thresholdchanged(float,float)\0"
};

void amyDoubleThresholdWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyDoubleThresholdWidget *_t = static_cast<amyDoubleThresholdWidget *>(_o);
        switch (_id) {
        case 0: _t->s_thresholdchanging((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->s_thresholdchanged((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyDoubleThresholdWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyDoubleThresholdWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amyDoubleThresholdWidget,
      qt_meta_data_amyDoubleThresholdWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyDoubleThresholdWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyDoubleThresholdWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyDoubleThresholdWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyDoubleThresholdWidget))
        return static_cast<void*>(const_cast< amyDoubleThresholdWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int amyDoubleThresholdWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void amyDoubleThresholdWidget::s_thresholdchanging(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void amyDoubleThresholdWidget::s_thresholdchanged(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
