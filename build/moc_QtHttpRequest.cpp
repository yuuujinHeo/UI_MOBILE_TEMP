/****************************************************************************
** Meta object code from reading C++ file 'QtHttpRequest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../websocket/QtHttpRequest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtHttpRequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtHttpRequest_t {
    QByteArrayData data[11];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtHttpRequest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtHttpRequest_t qt_meta_stringdata_QtHttpRequest = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtHttpRequest"
QT_MOC_LITERAL(1, 14, 6), // "setUrl"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "url"
QT_MOC_LITERAL(4, 26, 10), // "setCommand"
QT_MOC_LITERAL(5, 37, 7), // "command"
QT_MOC_LITERAL(6, 45, 9), // "addHeader"
QT_MOC_LITERAL(7, 55, 6), // "header"
QT_MOC_LITERAL(8, 62, 5), // "value"
QT_MOC_LITERAL(9, 68, 13), // "appendRawData"
QT_MOC_LITERAL(10, 82, 4) // "data"

    },
    "QtHttpRequest\0setUrl\0\0url\0setCommand\0"
    "command\0addHeader\0header\0value\0"
    "appendRawData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtHttpRequest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    2,   40,    2, 0x0a /* Public */,
       9,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    7,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,

       0        // eod
};

void QtHttpRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtHttpRequest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setUrl((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: _t->setCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->addHeader((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 3: _t->appendRawData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtHttpRequest::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QtHttpRequest.data,
    qt_meta_data_QtHttpRequest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtHttpRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtHttpRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtHttpRequest.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtHttpRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
