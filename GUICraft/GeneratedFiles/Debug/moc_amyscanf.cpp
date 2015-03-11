/****************************************************************************
** Meta object code from reading C++ file 'amyscanf.h'
**
** Created: Wed Mar 11 01:25:44 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyscanf.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyscanf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyUtil__ScanfPatternDialog[] = {

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
      29,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyUtil__ScanfPatternDialog[] = {
    "amyUtil::ScanfPatternDialog\0\0OnOk()\0"
};

void amyUtil::ScanfPatternDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScanfPatternDialog *_t = static_cast<ScanfPatternDialog *>(_o);
        switch (_id) {
        case 0: _t->OnOk(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyUtil::ScanfPatternDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyUtil::ScanfPatternDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_amyUtil__ScanfPatternDialog,
      qt_meta_data_amyUtil__ScanfPatternDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyUtil::ScanfPatternDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyUtil::ScanfPatternDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyUtil::ScanfPatternDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyUtil__ScanfPatternDialog))
        return static_cast<void*>(const_cast< ScanfPatternDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int amyUtil::ScanfPatternDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_amyUtil__ScanfArrDialog[] = {

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
      25,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyUtil__ScanfArrDialog[] = {
    "amyUtil::ScanfArrDialog\0\0OnOk()\0"
};

void amyUtil::ScanfArrDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScanfArrDialog *_t = static_cast<ScanfArrDialog *>(_o);
        switch (_id) {
        case 0: _t->OnOk(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyUtil::ScanfArrDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyUtil::ScanfArrDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_amyUtil__ScanfArrDialog,
      qt_meta_data_amyUtil__ScanfArrDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyUtil::ScanfArrDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyUtil::ScanfArrDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyUtil::ScanfArrDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyUtil__ScanfArrDialog))
        return static_cast<void*>(const_cast< ScanfArrDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int amyUtil::ScanfArrDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
