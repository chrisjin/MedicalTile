/****************************************************************************
** Meta object code from reading C++ file 'amyMaskEditor.h'
**
** Created: Fri Mar 21 11:14:59 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyMaskEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyMaskEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyMaskWidget[] = {

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
      17,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyMaskWidget[] = {
    "amyMaskWidget\0\0a\0SetTransp(int)\0"
};

void amyMaskWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyMaskWidget *_t = static_cast<amyMaskWidget *>(_o);
        switch (_id) {
        case 0: _t->SetTransp((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyMaskWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyMaskWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amyMaskWidget,
      qt_meta_data_amyMaskWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyMaskWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyMaskWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyMaskWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyMaskWidget))
        return static_cast<void*>(const_cast< amyMaskWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int amyMaskWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_ToolPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      21,   10,   10,   10, 0x05,
      30,   10,   10,   10, 0x05,
      46,   10,   10,   10, 0x05,
      63,   10,   10,   10, 0x05,
      78,   10,   10,   10, 0x05,
      89,   10,   10,   10, 0x05,
      98,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ToolPanel[] = {
    "ToolPanel\0\0s_erase()\0s_grow()\0"
    "s_growinslice()\0s_removeothers()\0"
    "s_removethis()\0s_noedit()\0s_draw()\0"
    "s_erasesize(int)\0"
};

void ToolPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToolPanel *_t = static_cast<ToolPanel *>(_o);
        switch (_id) {
        case 0: _t->s_erase(); break;
        case 1: _t->s_grow(); break;
        case 2: _t->s_growinslice(); break;
        case 3: _t->s_removeothers(); break;
        case 4: _t->s_removethis(); break;
        case 5: _t->s_noedit(); break;
        case 6: _t->s_draw(); break;
        case 7: _t->s_erasesize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ToolPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToolPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolPanel,
      qt_meta_data_ToolPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolPanel))
        return static_cast<void*>(const_cast< ToolPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToolPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ToolPanel::s_erase()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ToolPanel::s_grow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ToolPanel::s_growinslice()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ToolPanel::s_removeothers()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ToolPanel::s_removethis()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ToolPanel::s_noedit()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ToolPanel::s_draw()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ToolPanel::s_erasesize(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
static const uint qt_meta_data_amyMaskEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x0a,
      32,   14,   14,   14, 0x0a,
      42,   14,   14,   14, 0x0a,
      53,   14,   14,   14, 0x0a,
      71,   14,   14,   14, 0x0a,
      81,   14,   14,   14, 0x0a,
      93,   14,   14,   14, 0x0a,
     110,   14,   14,   14, 0x0a,
     129,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyMaskEditor[] = {
    "amyMaskEditor\0\0m\0SetMode(eMode)\0"
    "SetGrow()\0SetErase()\0SetEraseSize(int)\0"
    "SetDraw()\0SetNoEdit()\0SetGrowInSlice()\0"
    "RemoveOtherSlice()\0RemoveThisSlice()\0"
};

void amyMaskEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyMaskEditor *_t = static_cast<amyMaskEditor *>(_o);
        switch (_id) {
        case 0: _t->SetMode((*reinterpret_cast< eMode(*)>(_a[1]))); break;
        case 1: _t->SetGrow(); break;
        case 2: _t->SetErase(); break;
        case 3: _t->SetEraseSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetDraw(); break;
        case 5: _t->SetNoEdit(); break;
        case 6: _t->SetGrowInSlice(); break;
        case 7: _t->RemoveOtherSlice(); break;
        case 8: _t->RemoveThisSlice(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyMaskEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyMaskEditor::staticMetaObject = {
    { &amyVariableEditor::staticMetaObject, qt_meta_stringdata_amyMaskEditor,
      qt_meta_data_amyMaskEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyMaskEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyMaskEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyMaskEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyMaskEditor))
        return static_cast<void*>(const_cast< amyMaskEditor*>(this));
    return amyVariableEditor::qt_metacast(_clname);
}

int amyMaskEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = amyVariableEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
