/****************************************************************************
** Meta object code from reading C++ file 'amyVariableItem.h'
**
** Created: Wed Mar 11 01:25:43 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyVariableItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyVariableItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyVariableItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyVariableItem[] = {
    "amyVariableItem\0\0s_moveoutside()\0"
};

void amyVariableItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyVariableItem *_t = static_cast<amyVariableItem *>(_o);
        switch (_id) {
        case 0: _t->s_moveoutside(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyVariableItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyVariableItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_amyVariableItem,
      qt_meta_data_amyVariableItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyVariableItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyVariableItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyVariableItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyVariableItem))
        return static_cast<void*>(const_cast< amyVariableItem*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< amyVariableItem*>(this));
    if (!strcmp(_clname, "amyInput<amyVariable>"))
        return static_cast< amyInput<amyVariable>*>(const_cast< amyVariableItem*>(this));
    return QObject::qt_metacast(_clname);
}

int amyVariableItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void amyVariableItem::s_moveoutside()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
