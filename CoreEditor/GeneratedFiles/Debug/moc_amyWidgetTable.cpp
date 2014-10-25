/****************************************************************************
** Meta object code from reading C++ file 'amyWidgetTable.h'
**
** Created: Fri Mar 21 11:14:59 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyWidgetTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyWidgetTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyWidgetTableDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      38,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyWidgetTableDelegate[] = {
    "amyWidgetTableDelegate\0\0UpdateModel()\0"
    "UpdateView()\0"
};

void amyWidgetTableDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyWidgetTableDelegate *_t = static_cast<amyWidgetTableDelegate *>(_o);
        switch (_id) {
        case 0: _t->UpdateModel(); break;
        case 1: _t->UpdateView(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyWidgetTableDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyWidgetTableDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_amyWidgetTableDelegate,
      qt_meta_data_amyWidgetTableDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyWidgetTableDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyWidgetTableDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyWidgetTableDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyWidgetTableDelegate))
        return static_cast<void*>(const_cast< amyWidgetTableDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int amyWidgetTableDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_amyWidgetTableArea[] = {

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

static const char qt_meta_stringdata_amyWidgetTableArea[] = {
    "amyWidgetTableArea\0"
};

void amyWidgetTableArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyWidgetTableArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyWidgetTableArea::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_amyWidgetTableArea,
      qt_meta_data_amyWidgetTableArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyWidgetTableArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyWidgetTableArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyWidgetTableArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyWidgetTableArea))
        return static_cast<void*>(const_cast< amyWidgetTableArea*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int amyWidgetTableArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_amyWidgetTableView[] = {

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

static const char qt_meta_stringdata_amyWidgetTableView[] = {
    "amyWidgetTableView\0"
};

void amyWidgetTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyWidgetTableView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyWidgetTableView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amyWidgetTableView,
      qt_meta_data_amyWidgetTableView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyWidgetTableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyWidgetTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyWidgetTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyWidgetTableView))
        return static_cast<void*>(const_cast< amyWidgetTableView*>(this));
    return QWidget::qt_metacast(_clname);
}

int amyWidgetTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
