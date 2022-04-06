/****************************************************************************
** Meta object code from reading C++ file 'st_client_table.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/smartlink/st_client_table.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_client_table.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExampleServer__st_client_table_t {
    QByteArrayData data[24];
    char stringdata0[415];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExampleServer__st_client_table_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExampleServer__st_client_table_t qt_meta_stringdata_ExampleServer__st_client_table = {
    {
QT_MOC_LITERAL(0, 0, 30), // "ExampleServer::st_client_table"
QT_MOC_LITERAL(1, 31, 11), // "evt_Message"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "psource"
QT_MOC_LITERAL(4, 52, 16), // "evt_addNewClient"
QT_MOC_LITERAL(5, 69, 5), // "pSock"
QT_MOC_LITERAL(6, 75, 15), // "evt_clientClose"
QT_MOC_LITERAL(7, 91, 18), // "evt_AddNewClientOk"
QT_MOC_LITERAL(8, 110, 25), // "on_evt_NewClientConnected"
QT_MOC_LITERAL(9, 136, 9), // "datablock"
QT_MOC_LITERAL(10, 146, 22), // "on_evt_ClientEncrypted"
QT_MOC_LITERAL(11, 169, 25), // "on_evt_ClientDisconnected"
QT_MOC_LITERAL(12, 195, 20), // "on_evt_Data_recieved"
QT_MOC_LITERAL(13, 216, 23), // "on_evt_Data_transferred"
QT_MOC_LITERAL(14, 240, 22), // "on_evt_NewSvrConnected"
QT_MOC_LITERAL(15, 263, 25), // "on_evt_NewSvrDisconnected"
QT_MOC_LITERAL(16, 289, 26), // "on_evt_RemoteData_recieved"
QT_MOC_LITERAL(17, 316, 29), // "on_evt_RemoteData_transferred"
QT_MOC_LITERAL(18, 346, 10), // "SendToNode"
QT_MOC_LITERAL(19, 357, 4), // "uuid"
QT_MOC_LITERAL(20, 362, 3), // "msg"
QT_MOC_LITERAL(21, 366, 15), // "KickDeadClients"
QT_MOC_LITERAL(22, 382, 17), // "CleanNoActiveNode"
QT_MOC_LITERAL(23, 400, 14) // "CleanDeadNodes"

    },
    "ExampleServer::st_client_table\0"
    "evt_Message\0\0psource\0evt_addNewClient\0"
    "pSock\0evt_clientClose\0evt_AddNewClientOk\0"
    "on_evt_NewClientConnected\0datablock\0"
    "on_evt_ClientEncrypted\0on_evt_ClientDisconnected\0"
    "on_evt_Data_recieved\0on_evt_Data_transferred\0"
    "on_evt_NewSvrConnected\0on_evt_NewSvrDisconnected\0"
    "on_evt_RemoteData_recieved\0"
    "on_evt_RemoteData_transferred\0SendToNode\0"
    "uuid\0msg\0KickDeadClients\0CleanNoActiveNode\0"
    "CleanDeadNodes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExampleServer__st_client_table[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       4,    1,  104,    2, 0x06 /* Public */,
       6,    1,  107,    2, 0x06 /* Public */,
       7,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,  113,    2, 0x09 /* Protected */,
      10,    1,  118,    2, 0x09 /* Protected */,
      11,    1,  121,    2, 0x09 /* Protected */,
      12,    2,  124,    2, 0x09 /* Protected */,
      13,    2,  129,    2, 0x09 /* Protected */,
      14,    1,  134,    2, 0x09 /* Protected */,
      15,    1,  137,    2, 0x09 /* Protected */,
      16,    2,  140,    2, 0x09 /* Protected */,
      17,    2,  145,    2, 0x09 /* Protected */,
      18,    2,  150,    2, 0x0a /* Public */,
      21,    0,  155,    2, 0x0a /* Public */,
      22,    0,  156,    2, 0x0a /* Public */,
      23,    0,  157,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar,    5,
    QMetaType::Void, QMetaType::QObjectStar,    5,
    QMetaType::Void, QMetaType::QObjectStar,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,    2,    9,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::LongLong,    2,    2,
    QMetaType::Bool, QMetaType::ULongLong, QMetaType::QByteArray,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExampleServer::st_client_table::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<st_client_table *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->evt_addNewClient((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->evt_clientClose((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 3: _t->evt_AddNewClientOk((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 4: _t->on_evt_NewClientConnected((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->on_evt_ClientEncrypted((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 6: _t->on_evt_ClientDisconnected((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->on_evt_Data_recieved((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 8: _t->on_evt_Data_transferred((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 9: _t->on_evt_NewSvrConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_evt_NewSvrDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_evt_RemoteData_recieved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 12: _t->on_evt_RemoteData_transferred((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 13: { bool _r = _t->SendToNode((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->KickDeadClients(); break;
        case 15: _t->CleanNoActiveNode(); break;
        case 16: _t->CleanDeadNodes(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (st_client_table::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_client_table::evt_Message)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (st_client_table::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_client_table::evt_addNewClient)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (st_client_table::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_client_table::evt_clientClose)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (st_client_table::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_client_table::evt_AddNewClientOk)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExampleServer::st_client_table::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ExampleServer__st_client_table.data,
    qt_meta_data_ExampleServer__st_client_table,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExampleServer::st_client_table::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExampleServer::st_client_table::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExampleServer__st_client_table.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExampleServer::st_client_table::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ExampleServer::st_client_table::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExampleServer::st_client_table::evt_addNewClient(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExampleServer::st_client_table::evt_clientClose(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ExampleServer::st_client_table::evt_AddNewClientOk(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
