/****************************************************************************
** Meta object code from reading C++ file 'zp_clusterterm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/cluster/zp_clusterterm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_clusterterm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm_t {
    QByteArrayData data[24];
    char stringdata0[386];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm_t qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ZP_Cluster::zp_ClusterTerm"
QT_MOC_LITERAL(1, 27, 11), // "evt_Message"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15), // "evt_SocketError"
QT_MOC_LITERAL(4, 56, 10), // "senderSock"
QT_MOC_LITERAL(5, 67, 4), // "erro"
QT_MOC_LITERAL(6, 72, 19), // "evt_NewSvrConnected"
QT_MOC_LITERAL(7, 92, 22), // "evt_NewSvrDisconnected"
QT_MOC_LITERAL(8, 115, 23), // "evt_RemoteData_recieved"
QT_MOC_LITERAL(9, 139, 26), // "evt_RemoteData_transferred"
QT_MOC_LITERAL(10, 166, 25), // "on_evt_NewClientConnected"
QT_MOC_LITERAL(11, 192, 22), // "on_evt_ClientEncrypted"
QT_MOC_LITERAL(12, 215, 25), // "on_evt_ClientDisconnected"
QT_MOC_LITERAL(13, 241, 20), // "on_evt_Data_recieved"
QT_MOC_LITERAL(14, 262, 23), // "on_evt_Data_transferred"
QT_MOC_LITERAL(15, 286, 11), // "StartListen"
QT_MOC_LITERAL(16, 298, 12), // "QHostAddress"
QT_MOC_LITERAL(17, 311, 4), // "addr"
QT_MOC_LITERAL(18, 316, 5), // "nPort"
QT_MOC_LITERAL(19, 322, 11), // "JoinCluster"
QT_MOC_LITERAL(20, 334, 4), // "bSSL"
QT_MOC_LITERAL(21, 339, 15), // "KickDeadClients"
QT_MOC_LITERAL(22, 355, 22), // "SendDataToRemoteServer"
QT_MOC_LITERAL(23, 378, 7) // "svrName"

    },
    "ZP_Cluster::zp_ClusterTerm\0evt_Message\0"
    "\0evt_SocketError\0senderSock\0erro\0"
    "evt_NewSvrConnected\0evt_NewSvrDisconnected\0"
    "evt_RemoteData_recieved\0"
    "evt_RemoteData_transferred\0"
    "on_evt_NewClientConnected\0"
    "on_evt_ClientEncrypted\0on_evt_ClientDisconnected\0"
    "on_evt_Data_recieved\0on_evt_Data_transferred\0"
    "StartListen\0QHostAddress\0addr\0nPort\0"
    "JoinCluster\0bSSL\0KickDeadClients\0"
    "SendDataToRemoteServer\0svrName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZP_Cluster__zp_ClusterTerm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       3,    2,   99,    2, 0x06 /* Public */,
       6,    1,  104,    2, 0x06 /* Public */,
       7,    1,  107,    2, 0x06 /* Public */,
       8,    2,  110,    2, 0x06 /* Public */,
       9,    2,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  120,    2, 0x09 /* Protected */,
      11,    1,  123,    2, 0x09 /* Protected */,
      12,    1,  126,    2, 0x09 /* Protected */,
      13,    2,  129,    2, 0x09 /* Protected */,
      14,    2,  134,    2, 0x09 /* Protected */,
      15,    2,  139,    2, 0x0a /* Public */,
      19,    3,  144,    2, 0x0a /* Public */,
      19,    2,  151,    2, 0x2a /* Public | MethodCloned */,
      21,    0,  156,    2, 0x0a /* Public */,
      22,    2,  157,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::LongLong,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::LongLong,    2,    2,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   17,   18,
    QMetaType::Bool, 0x80000000 | 16, QMetaType::Int, QMetaType::Bool,   17,   18,   20,
    QMetaType::Bool, 0x80000000 | 16, QMetaType::Int,   17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   23,    2,

       0        // eod
};

void ZP_Cluster::zp_ClusterTerm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zp_ClusterTerm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->evt_SocketError((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->evt_NewSvrConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->evt_NewSvrDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->evt_RemoteData_recieved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->evt_RemoteData_transferred((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: _t->on_evt_NewClientConnected((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->on_evt_ClientEncrypted((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 8: _t->on_evt_ClientDisconnected((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 9: _t->on_evt_Data_recieved((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 10: _t->on_evt_Data_transferred((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 11: _t->StartListen((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: { bool _r = _t->JoinCluster((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->JoinCluster((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->KickDeadClients(); break;
        case 15: _t->SendDataToRemoteServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (zp_ClusterTerm::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_Message)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (zp_ClusterTerm::*)(QObject * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_SocketError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (zp_ClusterTerm::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_NewSvrConnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (zp_ClusterTerm::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_NewSvrDisconnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (zp_ClusterTerm::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_RemoteData_recieved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (zp_ClusterTerm::*)(QObject * , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterTerm::evt_RemoteData_transferred)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZP_Cluster::zp_ClusterTerm::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm.data,
    qt_meta_data_ZP_Cluster__zp_ClusterTerm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZP_Cluster::zp_ClusterTerm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZP_Cluster::zp_ClusterTerm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZP_Cluster__zp_ClusterTerm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZP_Cluster::zp_ClusterTerm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ZP_Cluster::zp_ClusterTerm::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZP_Cluster::zp_ClusterTerm::evt_SocketError(QObject * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZP_Cluster::zp_ClusterTerm::evt_NewSvrConnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZP_Cluster::zp_ClusterTerm::evt_NewSvrDisconnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZP_Cluster::zp_ClusterTerm::evt_RemoteData_recieved(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZP_Cluster::zp_ClusterTerm::evt_RemoteData_transferred(QObject * _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
