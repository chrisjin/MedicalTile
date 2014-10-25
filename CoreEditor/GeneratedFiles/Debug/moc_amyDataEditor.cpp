/****************************************************************************
** Meta object code from reading C++ file 'amyDataEditor.h'
**
** Created: Fri Mar 21 11:14:58 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyDataEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyDataEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataRoleTableModel[] = {

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

static const char qt_meta_stringdata_DataRoleTableModel[] = {
    "DataRoleTableModel\0"
};

void DataRoleTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DataRoleTableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataRoleTableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_DataRoleTableModel,
      qt_meta_data_DataRoleTableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataRoleTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataRoleTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataRoleTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataRoleTableModel))
        return static_cast<void*>(const_cast< DataRoleTableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int DataRoleTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DataRoleTableDelegate[] = {

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

static const char qt_meta_stringdata_DataRoleTableDelegate[] = {
    "DataRoleTableDelegate\0"
};

void DataRoleTableDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DataRoleTableDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataRoleTableDelegate::staticMetaObject = {
    { &amyWidgetTableDelegate::staticMetaObject, qt_meta_stringdata_DataRoleTableDelegate,
      qt_meta_data_DataRoleTableDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataRoleTableDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataRoleTableDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataRoleTableDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataRoleTableDelegate))
        return static_cast<void*>(const_cast< DataRoleTableDelegate*>(this));
    return amyWidgetTableDelegate::qt_metacast(_clname);
}

int DataRoleTableDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyWidgetTableDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_amyDataEditor[] = {

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
      15,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyDataEditor[] = {
    "amyDataEditor\0\0UpdateBarRange()\0"
};

void amyDataEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyDataEditor *_t = static_cast<amyDataEditor *>(_o);
        switch (_id) {
        case 0: _t->UpdateBarRange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyDataEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyDataEditor::staticMetaObject = {
    { &amyVariableEditor::staticMetaObject, qt_meta_stringdata_amyDataEditor,
      qt_meta_data_amyDataEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyDataEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyDataEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyDataEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyDataEditor))
        return static_cast<void*>(const_cast< amyDataEditor*>(this));
    return amyVariableEditor::qt_metacast(_clname);
}

int amyDataEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyVariableEditor::qt_metacall(_c, _id, _a);
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
