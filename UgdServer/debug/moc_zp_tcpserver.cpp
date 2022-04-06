/****************************************************************************
** Meta object code from reading C++ file 'zp_tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/network/zp_tcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_tcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPNetwork__ZP_TcpServer_t {
    QByteArrayData data[4];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPNetwork__ZP_TcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPNetwork__ZP_TcpServer_t qt_meta_stringdata_ZPNetwork__ZP_TcpServer = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ZPNetwork::ZP_TcpServer"
QT_MOC_LITERAL(1, 24, 20), // "evt_NewClientArrived"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 7) // "session"

    },
    "ZPNetwork::ZP_TcpServer\0evt_NewClientArrived\0"
    "\0session"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPNetwork__ZP_TcpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::VoidStar,    3,

       0        // eod
};

void ZPNetwork::ZP_TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ZP_TcpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_NewClientArrived((*reinterpret_cast< void*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ZP_TcpServer::*)(void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZP_TcpServer::evt_NewClientArrived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZPNetwork::ZP_TcpServer::staticMetaObject = { {
    &QAsioTcpServer::staticMetaObject,
    qt_meta_stringdata_ZPNetwork__ZP_TcpServer.data,
    qt_meta_data_ZPNetwork__ZP_TcpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZPNetwork::ZP_TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPNetwork::ZP_TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPNetwork__ZP_TcpServer.stringdata0))
        return static_cast<void*>(this);
    return QAsioTcpServer::qt_metacast(_clname);
}

int ZPNetwork::ZP_TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAsioTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ZPNetwork::ZP_TcpServer::evt_NewClientArrived(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
