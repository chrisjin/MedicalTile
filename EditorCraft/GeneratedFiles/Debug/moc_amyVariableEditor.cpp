/****************************************************************************
** Meta object code from reading C++ file 'amyVariableEditor.h'
**
** Created: Wed Mar 11 01:25:33 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyVariableEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyVariableEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyVariableEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      31,   18,   18,   18, 0x05,
      42,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   18,   18,   18, 0x0a,
      66,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyVariableEditor[] = {
    "amyVariableEditor\0\0s_confirm()\0"
    "s_cancel()\0s_close()\0SlotConfirm()\0"
    "SlotCancel()\0"
};

void amyVariableEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyVariableEditor *_t = static_cast<amyVariableEditor *>(_o);
        switch (_id) {
        case 0: _t->s_confirm(); break;
        case 1: _t->s_cancel(); break;
        case 2: _t->s_close(); break;
        case 3: _t->SlotConfirm(); break;
        case 4: _t->SlotCancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyVariableEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyVariableEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_amyVariableEditor,
      qt_meta_data_amyVariableEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyVariableEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyVariableEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyVariableEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyVariableEditor))
        return static_cast<void*>(const_cast< amyVariableEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int amyVariableEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void amyVariableEditor::s_confirm()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void amyVariableEditor::s_cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void amyVariableEditor::s_close()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
