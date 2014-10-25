/****************************************************************************
** Meta object code from reading C++ file 'QAMYWindow.h'
**
** Created: Fri Mar 21 11:15:41 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QAMYWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QAMYWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QAMYWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      24,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      61,   11,   11,   11, 0x0a,
      69,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QAMYWindow[] = {
    "QAMYWindow\0\0SetSamize()\0SwitchMeasurementMode()\0"
    "OpenFolder()\0Set2D()\0Set3DAndMPR()\0"
};

void QAMYWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QAMYWindow *_t = static_cast<QAMYWindow *>(_o);
        switch (_id) {
        case 0: _t->SetSamize(); break;
        case 1: _t->SwitchMeasurementMode(); break;
        case 2: _t->OpenFolder(); break;
        case 3: _t->Set2D(); break;
        case 4: _t->Set3DAndMPR(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QAMYWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QAMYWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QAMYWindow,
      qt_meta_data_QAMYWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QAMYWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QAMYWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QAMYWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QAMYWindow))
        return static_cast<void*>(const_cast< QAMYWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QAMYWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
