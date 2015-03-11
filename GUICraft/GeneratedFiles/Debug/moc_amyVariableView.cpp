/****************************************************************************
** Meta object code from reading C++ file 'amyVariableView.h'
**
** Created: Wed Mar 11 01:25:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyVariableView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyVariableView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyVariableScene[] = {

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

static const char qt_meta_stringdata_amyVariableScene[] = {
    "amyVariableScene\0"
};

void amyVariableScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyVariableScene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyVariableScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_amyVariableScene,
      qt_meta_data_amyVariableScene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyVariableScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyVariableScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyVariableScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyVariableScene))
        return static_cast<void*>(const_cast< amyVariableScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int amyVariableScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_amyVariableView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyVariableView[] = {
    "amyVariableView\0\0s_contextmenu(QPoint)\0"
    "DeleteSelected()\0"
};

void amyVariableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyVariableView *_t = static_cast<amyVariableView *>(_o);
        switch (_id) {
        case 0: _t->s_contextmenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->DeleteSelected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyVariableView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyVariableView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_amyVariableView,
      qt_meta_data_amyVariableView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyVariableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyVariableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyVariableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyVariableView))
        return static_cast<void*>(const_cast< amyVariableView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int amyVariableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
void amyVariableView::s_contextmenu(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
