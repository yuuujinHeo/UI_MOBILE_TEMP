/****************************************************************************
** Meta object code from reading C++ file 'ExtProcess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ExtProcess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExtProcess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExtProcess_t {
    QByteArrayData data[9];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtProcess_t qt_meta_stringdata_ExtProcess = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ExtProcess"
QT_MOC_LITERAL(1, 11, 10), // "got_accept"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "cmd"
QT_MOC_LITERAL(4, 27, 8), // "got_done"
QT_MOC_LITERAL(5, 36, 9), // "got_error"
QT_MOC_LITERAL(6, 46, 7), // "timeout"
QT_MOC_LITERAL(7, 54, 7), // "onTimer"
QT_MOC_LITERAL(8, 62, 10) // "onTimer500"

    },
    "ExtProcess\0got_accept\0\0cmd\0got_done\0"
    "got_error\0timeout\0onTimer\0onTimer500"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,
       6,    1,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExtProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExtProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->got_accept((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->got_done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->got_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->timeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onTimer(); break;
        case 5: _t->onTimer500(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExtProcess::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtProcess::got_accept)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExtProcess::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtProcess::got_done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ExtProcess::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtProcess::got_error)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ExtProcess::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtProcess::timeout)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExtProcess::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ExtProcess.data,
    qt_meta_data_ExtProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExtProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtProcess.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExtProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ExtProcess::got_accept(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtProcess::got_done(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExtProcess::got_error(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ExtProcess::timeout(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
