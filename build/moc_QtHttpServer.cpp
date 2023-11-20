/****************************************************************************
** Meta object code from reading C++ file 'QtHttpServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../websocket/QtHttpServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtHttpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtHttpServerWrapper_t {
    QByteArrayData data[1];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtHttpServerWrapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtHttpServerWrapper_t qt_meta_stringdata_QtHttpServerWrapper = {
    {
QT_MOC_LITERAL(0, 0, 19) // "QtHttpServerWrapper"

    },
    "QtHttpServerWrapper"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtHttpServerWrapper[] = {

 // content:
       8,       // revision
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

void QtHttpServerWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QtHttpServerWrapper::staticMetaObject = { {
    &QTcpServer::staticMetaObject,
    qt_meta_stringdata_QtHttpServerWrapper.data,
    qt_meta_data_QtHttpServerWrapper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtHttpServerWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtHttpServerWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtHttpServerWrapper.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int QtHttpServerWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QtHttpServer_t {
    QByteArrayData data[41];
    char stringdata0[485];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtHttpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtHttpServer_t qt_meta_stringdata_QtHttpServer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QtHttpServer"
QT_MOC_LITERAL(1, 13, 7), // "started"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "port"
QT_MOC_LITERAL(4, 27, 7), // "stopped"
QT_MOC_LITERAL(5, 35, 5), // "error"
QT_MOC_LITERAL(6, 41, 3), // "msg"
QT_MOC_LITERAL(7, 45, 15), // "clientConnected"
QT_MOC_LITERAL(8, 61, 4), // "guid"
QT_MOC_LITERAL(9, 66, 18), // "clientDisconnected"
QT_MOC_LITERAL(10, 85, 17), // "requestNeedsReply"
QT_MOC_LITERAL(11, 103, 14), // "QtHttpRequest*"
QT_MOC_LITERAL(12, 118, 7), // "request"
QT_MOC_LITERAL(13, 126, 12), // "QtHttpReply*"
QT_MOC_LITERAL(14, 139, 5), // "reply"
QT_MOC_LITERAL(15, 145, 17), // "clientConnectInfo"
QT_MOC_LITERAL(16, 163, 6), // "peerIp"
QT_MOC_LITERAL(17, 170, 5), // "start"
QT_MOC_LITERAL(18, 176, 4), // "stop"
QT_MOC_LITERAL(19, 181, 13), // "setServerName"
QT_MOC_LITERAL(20, 195, 10), // "serverName"
QT_MOC_LITERAL(21, 206, 12), // "setUseSecure"
QT_MOC_LITERAL(22, 219, 3), // "ssl"
QT_MOC_LITERAL(23, 223, 13), // "setPrivateKey"
QT_MOC_LITERAL(24, 237, 7), // "QSslKey"
QT_MOC_LITERAL(25, 245, 3), // "key"
QT_MOC_LITERAL(26, 249, 15), // "setCertificates"
QT_MOC_LITERAL(27, 265, 22), // "QList<QSslCertificate>"
QT_MOC_LITERAL(28, 288, 5), // "certs"
QT_MOC_LITERAL(29, 294, 17), // "onClientConnected"
QT_MOC_LITERAL(30, 312, 20), // "onClientDisconnected"
QT_MOC_LITERAL(31, 333, 20), // "onClientSslEncrypted"
QT_MOC_LITERAL(32, 354, 26), // "onClientSslPeerVerifyError"
QT_MOC_LITERAL(33, 381, 9), // "QSslError"
QT_MOC_LITERAL(34, 391, 3), // "err"
QT_MOC_LITERAL(35, 395, 17), // "onClientSslErrors"
QT_MOC_LITERAL(36, 413, 16), // "QList<QSslError>"
QT_MOC_LITERAL(37, 430, 6), // "errors"
QT_MOC_LITERAL(38, 437, 22), // "onClientSslModeChanged"
QT_MOC_LITERAL(39, 460, 19), // "QSslSocket::SslMode"
QT_MOC_LITERAL(40, 480, 4) // "mode"

    },
    "QtHttpServer\0started\0\0port\0stopped\0"
    "error\0msg\0clientConnected\0guid\0"
    "clientDisconnected\0requestNeedsReply\0"
    "QtHttpRequest*\0request\0QtHttpReply*\0"
    "reply\0clientConnectInfo\0peerIp\0start\0"
    "stop\0setServerName\0serverName\0"
    "setUseSecure\0ssl\0setPrivateKey\0QSslKey\0"
    "key\0setCertificates\0QList<QSslCertificate>\0"
    "certs\0onClientConnected\0onClientDisconnected\0"
    "onClientSslEncrypted\0onClientSslPeerVerifyError\0"
    "QSslError\0err\0onClientSslErrors\0"
    "QList<QSslError>\0errors\0onClientSslModeChanged\0"
    "QSslSocket::SslMode\0mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtHttpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       4,    0,  122,    2, 0x06 /* Public */,
       5,    1,  123,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,
       9,    1,  129,    2, 0x06 /* Public */,
      10,    2,  132,    2, 0x06 /* Public */,
      15,    1,  137,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  140,    2, 0x0a /* Public */,
      17,    0,  143,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  144,    2, 0x0a /* Public */,
      19,    1,  145,    2, 0x0a /* Public */,
      21,    1,  148,    2, 0x0a /* Public */,
      21,    0,  151,    2, 0x2a /* Public | MethodCloned */,
      23,    1,  152,    2, 0x0a /* Public */,
      26,    1,  155,    2, 0x0a /* Public */,
      29,    0,  158,    2, 0x08 /* Private */,
      30,    0,  159,    2, 0x08 /* Private */,
      31,    0,  160,    2, 0x08 /* Private */,
      32,    1,  161,    2, 0x08 /* Private */,
      35,    1,  164,    2, 0x08 /* Private */,
      38,    1,  167,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::QString,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 39,   40,

       0        // eod
};

void QtHttpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtHttpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 1: _t->stopped(); break;
        case 2: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->clientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->clientDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->requestNeedsReply((*reinterpret_cast< QtHttpRequest*(*)>(_a[1])),(*reinterpret_cast< QtHttpReply*(*)>(_a[2]))); break;
        case 6: _t->clientConnectInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->start((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->start(); break;
        case 9: _t->stop(); break;
        case 10: _t->setServerName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->setUseSecure((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 12: _t->setUseSecure(); break;
        case 13: _t->setPrivateKey((*reinterpret_cast< const QSslKey(*)>(_a[1]))); break;
        case 14: _t->setCertificates((*reinterpret_cast< const QList<QSslCertificate>(*)>(_a[1]))); break;
        case 15: _t->onClientConnected(); break;
        case 16: _t->onClientDisconnected(); break;
        case 17: _t->onClientSslEncrypted(); break;
        case 18: _t->onClientSslPeerVerifyError((*reinterpret_cast< const QSslError(*)>(_a[1]))); break;
        case 19: _t->onClientSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 20: _t->onClientSslModeChanged((*reinterpret_cast< QSslSocket::SslMode(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslCertificate> >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtHttpServer::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::started)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::error)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::clientConnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::clientDisconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)(QtHttpRequest * , QtHttpReply * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::requestNeedsReply)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QtHttpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpServer::clientConnectInfo)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtHttpServer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QtHttpServer.data,
    qt_meta_data_QtHttpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtHttpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtHttpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtHttpServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtHttpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void QtHttpServer::started(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtHttpServer::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QtHttpServer::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtHttpServer::clientConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtHttpServer::clientDisconnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QtHttpServer::requestNeedsReply(QtHttpRequest * _t1, QtHttpReply * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QtHttpServer::clientConnectInfo(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
