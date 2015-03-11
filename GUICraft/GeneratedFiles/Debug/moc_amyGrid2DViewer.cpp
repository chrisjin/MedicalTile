/****************************************************************************
** Meta object code from reading C++ file 'amyGrid2DViewer.h'
**
** Created: Wed Mar 11 01:25:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/amyGrid2DViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyGrid2DViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyGrid2DViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      26,   16,   16,   16, 0x0a,
      35,   16,   16,   16, 0x0a,
      44,   16,   16,   16, 0x0a,
      61,   16,   16,   16, 0x0a,
      77,   16,   16,   16, 0x0a,
     101,   16,   16,   16, 0x0a,
     113,   16,   16,   16, 0x0a,
     137,   16,   16,   16, 0x0a,
     157,   16,   16,   16, 0x0a,
     173,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_amyGrid2DViewer[] = {
    "amyGrid2DViewer\0\0Set1X1()\0Set2X2()\0"
    "Set3X3()\0SamizeSlice(int)\0SamizeZoom(int)\0"
    "SamizeTranslate(QPoint)\0SetSamize()\0"
    "SwitchMeasurementMode()\0DeleteMeasurement()\0"
    "ShowAnnotaion()\0Maximize()\0"
};

void amyGrid2DViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyGrid2DViewer *_t = static_cast<amyGrid2DViewer *>(_o);
        switch (_id) {
        case 0: _t->Set1X1(); break;
        case 1: _t->Set2X2(); break;
        case 2: _t->Set3X3(); break;
        case 3: _t->SamizeSlice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SamizeZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SamizeTranslate((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 6: _t->SetSamize(); break;
        case 7: _t->SwitchMeasurementMode(); break;
        case 8: _t->DeleteMeasurement(); break;
        case 9: _t->ShowAnnotaion(); break;
        case 10: _t->Maximize(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData amyGrid2DViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyGrid2DViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_amyGrid2DViewer,
      qt_meta_data_amyGrid2DViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyGrid2DViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyGrid2DViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyGrid2DViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyGrid2DViewer))
        return static_cast<void*>(const_cast< amyGrid2DViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int amyGrid2DViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
