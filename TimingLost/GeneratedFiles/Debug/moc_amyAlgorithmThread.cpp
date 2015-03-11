/****************************************************************************
** Meta object code from reading C++ file 'amyAlgorithmThread.h'
**
** Created: Wed Mar 11 01:37:36 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../amyAlgorithmThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amyAlgorithmThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_amyAlgorithmThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_amyAlgorithmThread[] = {
    "amyAlgorithmThread\0\0s_done()\0"
};

void amyAlgorithmThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        amyAlgorithmThread *_t = static_cast<amyAlgorithmThread *>(_o);
        switch (_id) {
        case 0: _t->s_done(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData amyAlgorithmThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject amyAlgorithmThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_amyAlgorithmThread,
      qt_meta_data_amyAlgorithmThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &amyAlgorithmThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *amyAlgorithmThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *amyAlgorithmThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_amyAlgorithmThread))
        return static_cast<void*>(const_cast< amyAlgorithmThread*>(this));
    return QThread::qt_metacast(_clname);
}

int amyAlgorithmThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void amyAlgorithmThread::s_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
