/****************************************************************************
** Meta object code from reading C++ file 'QtHttpReply.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../websocket/QtHttpReply.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtHttpReply.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtHttpReply_t {
    QByteArrayData data[25];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtHttpReply_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtHttpReply_t qt_meta_stringdata_QtHttpReply = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QtHttpReply"
QT_MOC_LITERAL(1, 12, 18), // "requestSendHeaders"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "requestSendData"
QT_MOC_LITERAL(4, 48, 13), // "setUseChunked"
QT_MOC_LITERAL(5, 62, 7), // "chunked"
QT_MOC_LITERAL(6, 70, 13), // "setStatusCode"
QT_MOC_LITERAL(7, 84, 10), // "StatusCode"
QT_MOC_LITERAL(8, 95, 10), // "statusCode"
QT_MOC_LITERAL(9, 106, 13), // "appendRawData"
QT_MOC_LITERAL(10, 120, 4), // "data"
QT_MOC_LITERAL(11, 125, 9), // "addHeader"
QT_MOC_LITERAL(12, 135, 6), // "header"
QT_MOC_LITERAL(13, 142, 5), // "value"
QT_MOC_LITERAL(14, 148, 12), // "resetRawData"
QT_MOC_LITERAL(15, 161, 2), // "Ok"
QT_MOC_LITERAL(16, 164, 8), // "SeeOther"
QT_MOC_LITERAL(17, 173, 10), // "BadRequest"
QT_MOC_LITERAL(18, 184, 9), // "Forbidden"
QT_MOC_LITERAL(19, 194, 8), // "NotFound"
QT_MOC_LITERAL(20, 203, 16), // "MethodNotAllowed"
QT_MOC_LITERAL(21, 220, 13), // "InternalError"
QT_MOC_LITERAL(22, 234, 14), // "NotImplemented"
QT_MOC_LITERAL(23, 249, 10), // "BadGateway"
QT_MOC_LITERAL(24, 260, 18) // "ServiceUnavailable"

    },
    "QtHttpReply\0requestSendHeaders\0\0"
    "requestSendData\0setUseChunked\0chunked\0"
    "setStatusCode\0StatusCode\0statusCode\0"
    "appendRawData\0data\0addHeader\0header\0"
    "value\0resetRawData\0Ok\0SeeOther\0"
    "BadRequest\0Forbidden\0NotFound\0"
    "MethodNotAllowed\0InternalError\0"
    "NotImplemented\0BadGateway\0ServiceUnavailable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtHttpReply[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       1,   72, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   56,    2, 0x0a /* Public */,
       4,    0,   59,    2, 0x2a /* Public | MethodCloned */,
       6,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      11,    2,   66,    2, 0x0a /* Public */,
      14,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,   12,   13,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       7,    7, 0x0,   10,   77,

 // enum data: key, value
      15, uint(QtHttpReply::Ok),
      16, uint(QtHttpReply::SeeOther),
      17, uint(QtHttpReply::BadRequest),
      18, uint(QtHttpReply::Forbidden),
      19, uint(QtHttpReply::NotFound),
      20, uint(QtHttpReply::MethodNotAllowed),
      21, uint(QtHttpReply::InternalError),
      22, uint(QtHttpReply::NotImplemented),
      23, uint(QtHttpReply::BadGateway),
      24, uint(QtHttpReply::ServiceUnavailable),

       0        // eod
};

void QtHttpReply::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtHttpReply *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestSendHeaders(); break;
        case 1: _t->requestSendData(); break;
        case 2: _t->setUseChunked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setUseChunked(); break;
        case 4: _t->setStatusCode((*reinterpret_cast< StatusCode(*)>(_a[1]))); break;
        case 5: _t->appendRawData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->addHeader((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 7: _t->resetRawData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtHttpReply::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpReply::requestSendHeaders)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtHttpReply::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtHttpReply::requestSendData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtHttpReply::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QtHttpReply.data,
    qt_meta_data_QtHttpReply,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtHttpReply::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtHttpReply::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtHttpReply.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtHttpReply::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QtHttpReply::requestSendHeaders()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QtHttpReply::requestSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
