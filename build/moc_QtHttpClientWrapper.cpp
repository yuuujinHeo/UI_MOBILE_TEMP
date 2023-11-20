/****************************************************************************
** Meta object code from reading C++ file 'QtHttpClientWrapper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../websocket/QtHttpClientWrapper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtHttpClientWrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtHttpClientWrapper_t {
    QByteArrayData data[5];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtHttpClientWrapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtHttpClientWrapper_t qt_meta_stringdata_QtHttpClientWrapper = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QtHttpClientWrapper"
QT_MOC_LITERAL(1, 20, 20), // "onClientDataReceived"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 27), // "onReplySendHeadersRequested"
QT_MOC_LITERAL(4, 70, 24) // "onReplySendDataRequested"

    },
    "QtHttpClientWrapper\0onClientDataReceived\0"
    "\0onReplySendHeadersRequested\0"
    "onReplySendDataRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtHttpClientWrapper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x09 /* Protected */,
       4,    0,   31,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtHttpClientWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtHttpClientWrapper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClientDataReceived(); break;
        case 1: _t->onReplySendHeadersRequested(); break;
        case 2: _t->onReplySendDataRequested(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QtHttpClientWrapper::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QtHttpClientWrapper.data,
    qt_meta_data_QtHttpClientWrapper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtHttpClientWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtHttpClientWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtHttpClientWrapper.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtHttpClientWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
