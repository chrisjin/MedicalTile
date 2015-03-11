/****************************************************************************
** Meta object code from reading C++ file 'amyAlgorithmScrollArea.h'
**
** Created: Wed Mar 11 01:26:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyAlgorithmScrollArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyAlgorithmScrollArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyAlgorithmScrollArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_amyAlgorithmScrollArea[] = {
    "amyAlgorithmScrollArea\0"
};

void amyAlgorithmScrollArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyAlgorithmScrollArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAlgorithmScrollArea::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_amyAlgorithmScrollArea,
      qt_meta_data_amyAlgorithmScrollArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAlgorithmScrollArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAlgorithmScrollArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAlgorithmScrollArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAlgorithmScrollArea))
        return static_cast<void*>(const_cast< amyAlgorithmScrollArea*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int amyAlgorithmScrollArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_WidgetForOneAlgorithm[] = {

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
      23,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetForOneAlgorithm[] = {
    "WidgetForOneAlgorithm\0\0ShowPanel()\0"
};

void WidgetForOneAlgorithm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetForOneAlgorithm *_t = static_cast<WidgetForOneAlgorithm *>(_o);
        switch (_id) {
        case 0: _t->ShowPanel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WidgetForOneAlgorithm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetForOneAlgorithm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetForOneAlgorithm,
      qt_meta_data_WidgetForOneAlgorithm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetForOneAlgorithm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetForOneAlgorithm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetForOneAlgorithm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetForOneAlgorithm))
        return static_cast<void*>(const_cast< WidgetForOneAlgorithm*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetForOneAlgorithm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
