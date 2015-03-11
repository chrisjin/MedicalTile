/****************************************************************************
** Meta object code from reading C++ file 'QAMYCuisineWindow.h'
**
** Created: Wed Mar 11 01:37:36 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QAMYCuisineWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QAMYCuisineWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QAMYCuisineWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   19,   18,   18, 0x0a,
      54,   18,   18,   18, 0x0a,
      74,   18,   18,   18, 0x0a,
      97,   18,   18,   18, 0x0a,
     113,   18,   18,   18, 0x0a,
     127,   18,   18,   18, 0x0a,
     145,   18,   18,   18, 0x0a,
     166,   18,   18,   18, 0x0a,
     185,   18,   18,   18, 0x0a,
     202,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QAMYCuisineWindow[] = {
    "QAMYCuisineWindow\0\0algo\0"
    "ApplyAlgorithm(amyAlgorithm*)\0"
    "SerializeSelected()\0DeseraializeSelected()\0"
    "BeginProgress()\0EndProgress()\0"
    "StepProgress(int)\0InputCheckingBegin()\0"
    "InputCheckingEnd()\0AlgorithmBegin()\0"
    "AlgorithmEnd()\0"
};

void QAMYCuisineWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QAMYCuisineWindow *_t = static_cast<QAMYCuisineWindow *>(_o);
        switch (_id) {
        case 0: _t->ApplyAlgorithm((*reinterpret_cast< amyAlgorithm*(*)>(_a[1]))); break;
        case 1: _t->SerializeSelected(); break;
        case 2: _t->DeseraializeSelected(); break;
        case 3: _t->BeginProgress(); break;
        case 4: _t->EndProgress(); break;
        case 5: _t->StepProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->InputCheckingBegin(); break;
        case 7: _t->InputCheckingEnd(); break;
        case 8: _t->AlgorithmBegin(); break;
        case 9: _t->AlgorithmEnd(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QAMYCuisineWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QAMYCuisineWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QAMYCuisineWindow,
      qt_meta_data_QAMYCuisineWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QAMYCuisineWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QAMYCuisineWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QAMYCuisineWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QAMYCuisineWindow))
        return static_cast<void*>(const_cast< QAMYCuisineWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QAMYCuisineWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
