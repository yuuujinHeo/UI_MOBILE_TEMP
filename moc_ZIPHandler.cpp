/****************************************************************************
** Meta object code from reading C++ file 'ZIPHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ZIPHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZIPHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZIPHandler_t {
    QByteArrayData data[6];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZIPHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZIPHandler_t qt_meta_stringdata_ZIPHandler = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ZIPHandler"
QT_MOC_LITERAL(1, 11, 8), // "zip_done"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "unzip_done"
QT_MOC_LITERAL(4, 32, 8), // "zip_fail"
QT_MOC_LITERAL(5, 41, 10) // "unzip_fail"

    },
    "ZIPHandler\0zip_done\0\0unzip_done\0"
    "zip_fail\0unzip_fail"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZIPHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZIPHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ZIPHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->zip_done(); break;
        case 1: _t->unzip_done(); break;
        case 2: _t->zip_fail(); break;
        case 3: _t->unzip_fail(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ZIPHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZIPHandler::zip_done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ZIPHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZIPHandler::unzip_done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ZIPHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZIPHandler::zip_fail)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ZIPHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZIPHandler::unzip_fail)) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ZIPHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZIPHandler.data,
    qt_meta_data_ZIPHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZIPHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZIPHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZIPHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZIPHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ZIPHandler::zip_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ZIPHandler::unzip_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ZIPHandler::zip_fail()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ZIPHandler::unzip_fail()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
