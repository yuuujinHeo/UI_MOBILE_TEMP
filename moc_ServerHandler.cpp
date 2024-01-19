/****************************************************************************
** Meta object code from reading C++ file 'ServerHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ServerHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerHandler_t {
    QByteArrayData data[12];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerHandler_t qt_meta_stringdata_ServerHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ServerHandler"
QT_MOC_LITERAL(1, 14, 10), // "updatefail"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "updatesuccess"
QT_MOC_LITERAL(4, 40, 12), // "newCallOrder"
QT_MOC_LITERAL(5, 53, 5), // "table"
QT_MOC_LITERAL(6, 59, 18), // "onCallRequestReply"
QT_MOC_LITERAL(7, 78, 14), // "QtHttpRequest*"
QT_MOC_LITERAL(8, 93, 7), // "request"
QT_MOC_LITERAL(9, 101, 12), // "QtHttpReply*"
QT_MOC_LITERAL(10, 114, 5), // "reply"
QT_MOC_LITERAL(11, 120, 7) // "onTimer"

    },
    "ServerHandler\0updatefail\0\0updatesuccess\0"
    "newCallOrder\0table\0onCallRequestReply\0"
    "QtHttpRequest*\0request\0QtHttpReply*\0"
    "reply\0onTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    1,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   44,    2, 0x08 /* Private */,
      11,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void,

       0        // eod
};

void ServerHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatefail(); break;
        case 1: _t->updatesuccess(); break;
        case 2: _t->newCallOrder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onCallRequestReply((*reinterpret_cast< QtHttpRequest*(*)>(_a[1])),(*reinterpret_cast< QtHttpReply*(*)>(_a[2]))); break;
        case 4: _t->onTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QtHttpReply* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QtHttpRequest* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerHandler::updatefail)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerHandler::updatesuccess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerHandler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerHandler::newCallOrder)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ServerHandler.data,
    qt_meta_data_ServerHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ServerHandler::updatefail()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ServerHandler::updatesuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ServerHandler::newCallOrder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
