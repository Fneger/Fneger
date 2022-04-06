/****************************************************************************
** Meta object code from reading C++ file 'zp_clusternode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/cluster/zp_clusternode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_clusternode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZP_Cluster__zp_ClusterNode_t {
    QByteArrayData data[15];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZP_Cluster__zp_ClusterNode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZP_Cluster__zp_ClusterNode_t qt_meta_stringdata_ZP_Cluster__zp_ClusterNode = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ZP_Cluster::zp_ClusterNode"
QT_MOC_LITERAL(1, 27, 20), // "evt_SendDataToClient"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 9), // "objClient"
QT_MOC_LITERAL(4, 59, 7), // "dtarray"
QT_MOC_LITERAL(5, 67, 16), // "evt_close_client"
QT_MOC_LITERAL(6, 84, 14), // "evt_connect_to"
QT_MOC_LITERAL(7, 99, 12), // "QHostAddress"
QT_MOC_LITERAL(8, 112, 7), // "address"
QT_MOC_LITERAL(9, 120, 5), // "nPort"
QT_MOC_LITERAL(10, 126, 8), // "bSSLConn"
QT_MOC_LITERAL(11, 135, 11), // "evt_Message"
QT_MOC_LITERAL(12, 147, 7), // "psource"
QT_MOC_LITERAL(13, 155, 19), // "evt_NewSvrConnected"
QT_MOC_LITERAL(14, 175, 23) // "evt_RemoteData_recieved"

    },
    "ZP_Cluster::zp_ClusterNode\0"
    "evt_SendDataToClient\0\0objClient\0dtarray\0"
    "evt_close_client\0evt_connect_to\0"
    "QHostAddress\0address\0nPort\0bSSLConn\0"
    "evt_Message\0psource\0evt_NewSvrConnected\0"
    "evt_RemoteData_recieved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZP_Cluster__zp_ClusterNode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    1,   49,    2, 0x06 /* Public */,
       6,    4,   52,    2, 0x06 /* Public */,
      11,    2,   61,    2, 0x06 /* Public */,
      13,    1,   66,    2, 0x06 /* Public */,
      14,    2,   69,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, 0x80000000 | 7, QMetaType::UShort, QMetaType::Bool, QMetaType::ULongLong,    8,    9,   10,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,   12,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,

       0        // eod
};

void ZP_Cluster::zp_ClusterNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zp_ClusterNode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_SendDataToClient((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->evt_close_client((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->evt_connect_to((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4]))); break;
        case 3: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->evt_NewSvrConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->evt_RemoteData_recieved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (zp_ClusterNode::*)(QObject * , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_SendDataToClient)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (zp_ClusterNode::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_close_client)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (zp_ClusterNode::*)(const QHostAddress & , quint16 , bool , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_connect_to)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (zp_ClusterNode::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_Message)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (zp_ClusterNode::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_NewSvrConnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (zp_ClusterNode::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_ClusterNode::evt_RemoteData_recieved)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZP_Cluster::zp_ClusterNode::staticMetaObject = { {
    &ZPTaskEngine::zp_plTaskBase::staticMetaObject,
    qt_meta_stringdata_ZP_Cluster__zp_ClusterNode.data,
    qt_meta_data_ZP_Cluster__zp_ClusterNode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZP_Cluster::zp_ClusterNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZP_Cluster::zp_ClusterNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZP_Cluster__zp_ClusterNode.stringdata0))
        return static_cast<void*>(this);
    return ZPTaskEngine::zp_plTaskBase::qt_metacast(_clname);
}

int ZP_Cluster::zp_ClusterNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZPTaskEngine::zp_plTaskBase::qt_metacall(_c, _id, _a);
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
void ZP_Cluster::zp_ClusterNode::evt_SendDataToClient(QObject * _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZP_Cluster::zp_ClusterNode::evt_close_client(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZP_Cluster::zp_ClusterNode::evt_connect_to(const QHostAddress & _t1, quint16 _t2, bool _t3, quint64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZP_Cluster::zp_ClusterNode::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZP_Cluster::zp_ClusterNode::evt_NewSvrConnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZP_Cluster::zp_ClusterNode::evt_RemoteData_recieved(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
