/****************************************************************************
** Meta object code from reading C++ file 'amySeriesSetEditor.h'
**
** Created: Wed Mar 11 01:26:43 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amySeriesSetEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amySeriesSetEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amySeriesWidget[] = {

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

static const char qt_meta_stringdata_amySeriesWidget[] = {
    "amySeriesWidget\0"
};

void amySeriesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amySeriesWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amySeriesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amySeriesWidget,
      qt_meta_data_amySeriesWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amySeriesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amySeriesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amySeriesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amySeriesWidget))
        return static_cast<void*>(const_cast< amySeriesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int amySeriesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_amySeriesSetEditor[] = {

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
      20,   19,   19,   19, 0x0a,
      38,   19,   19,   19, 0x0a,
      57,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amySeriesSetEditor[] = {
    "amySeriesSetEditor\0\0DeleteTableCell()\0"
    "RecoverTableCell()\0AfterConfirm()\0"
};

void amySeriesSetEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amySeriesSetEditor *_t = static_cast<amySeriesSetEditor *>(_o);
        switch (_id) {
        case 0: _t->DeleteTableCell(); break;
        case 1: _t->RecoverTableCell(); break;
        case 2: _t->AfterConfirm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amySeriesSetEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amySeriesSetEditor::staticMetaObject = {
    { &amyVariableEditor::staticMetaObject, qt_meta_stringdata_amySeriesSetEditor,
      qt_meta_data_amySeriesSetEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amySeriesSetEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amySeriesSetEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amySeriesSetEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amySeriesSetEditor))
        return static_cast<void*>(const_cast< amySeriesSetEditor*>(this));
    return amyVariableEditor::qt_metacast(_clname);
}

int amySeriesSetEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyVariableEditor::qt_metacall(_c, _id, _a);
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
