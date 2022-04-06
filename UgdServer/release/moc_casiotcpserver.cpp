/****************************************************************************
** Meta object code from reading C++ file 'casiotcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/asio/casiotcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'casiotcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CAsioTcpServer_t {
    QByteArrayData data[8];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAsioTcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAsioTcpServer_t qt_meta_stringdata_CAsioTcpServer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CAsioTcpServer"
QT_MOC_LITERAL(1, 15, 13), // "newConnection"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "CAsioTcpSocket*"
QT_MOC_LITERAL(4, 46, 6), // "socket"
QT_MOC_LITERAL(5, 53, 13), // "deleteAllLink"
QT_MOC_LITERAL(6, 67, 20), // "evt_NewClientArrived"
QT_MOC_LITERAL(7, 88, 7) // "session"

    },
    "CAsioTcpServer\0newConnection\0\0"
    "CAsioTcpSocket*\0socket\0deleteAllLink\0"
    "evt_NewClientArrived\0session"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAsioTcpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    0,   32,    2, 0x06 /* Public */,
       6,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar,    7,

       0        // eod
};

void CAsioTcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CAsioTcpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newConnection((*reinterpret_cast< CAsioTcpSocket*(*)>(_a[1]))); break;
        case 1: _t->deleteAllLink(); break;
        case 2: _t->evt_NewClientArrived((*reinterpret_cast< void*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CAsioTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CAsioTcpServer::*)(CAsioTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAsioTcpServer::newConnection)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CAsioTcpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAsioTcpServer::deleteAllLink)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CAsioTcpServer::*)(void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAsioTcpServer::evt_NewClientArrived)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CAsioTcpServer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CAsioTcpServer.data,
    qt_meta_data_CAsioTcpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CAsioTcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAsioTcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CAsioTcpServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CAsioTcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CAsioTcpServer::newConnection(CAsioTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CAsioTcpServer::deleteAllLink()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CAsioTcpServer::evt_NewClientArrived(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
