/****************************************************************************
** Meta object code from reading C++ file 'zp_nettransthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/network/zp_nettransthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_nettransthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPNetwork__zp_netTransThread_t {
    QByteArrayData data[42];
    char stringdata0[558];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPNetwork__zp_netTransThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPNetwork__zp_netTransThread_t qt_meta_stringdata_ZPNetwork__zp_netTransThread = {
    {
QT_MOC_LITERAL(0, 0, 28), // "ZPNetwork::zp_netTransThread"
QT_MOC_LITERAL(1, 29, 11), // "evt_Message"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7), // "psource"
QT_MOC_LITERAL(4, 50, 15), // "evt_SocketError"
QT_MOC_LITERAL(5, 66, 10), // "senderSock"
QT_MOC_LITERAL(6, 77, 4), // "erro"
QT_MOC_LITERAL(7, 82, 9), // "extraData"
QT_MOC_LITERAL(8, 92, 22), // "evt_NewClientConnected"
QT_MOC_LITERAL(9, 115, 6), // "client"
QT_MOC_LITERAL(10, 122, 2), // "ba"
QT_MOC_LITERAL(11, 125, 19), // "evt_ClientEncrypted"
QT_MOC_LITERAL(12, 145, 22), // "evt_ClientDisconnected"
QT_MOC_LITERAL(13, 168, 17), // "evt_Data_recieved"
QT_MOC_LITERAL(14, 186, 20), // "evt_Data_transferred"
QT_MOC_LITERAL(15, 207, 18), // "incomingConnection"
QT_MOC_LITERAL(16, 226, 8), // "threadid"
QT_MOC_LITERAL(17, 235, 7), // "session"
QT_MOC_LITERAL(18, 243, 15), // "startConnection"
QT_MOC_LITERAL(19, 259, 12), // "QHostAddress"
QT_MOC_LITERAL(20, 272, 4), // "addr"
QT_MOC_LITERAL(21, 277, 4), // "port"
QT_MOC_LITERAL(22, 282, 16), // "SendDataToClient"
QT_MOC_LITERAL(23, 299, 9), // "objClient"
QT_MOC_LITERAL(24, 309, 7), // "dtarray"
QT_MOC_LITERAL(25, 317, 10), // "Deactivate"
QT_MOC_LITERAL(26, 328, 21), // "DeactivateImmediately"
QT_MOC_LITERAL(27, 350, 18), // "zp_netTransThread*"
QT_MOC_LITERAL(28, 369, 14), // "KickAllClients"
QT_MOC_LITERAL(29, 384, 10), // "KickClient"
QT_MOC_LITERAL(30, 395, 23), // "KickRabishCanTimeOutObj"
QT_MOC_LITERAL(31, 419, 14), // "AddNewClientOk"
QT_MOC_LITERAL(32, 434, 5), // "pSock"
QT_MOC_LITERAL(33, 440, 14), // "EmptyRabishCan"
QT_MOC_LITERAL(34, 455, 9), // "pTransObj"
QT_MOC_LITERAL(35, 465, 13), // "client_closed"
QT_MOC_LITERAL(36, 479, 17), // "new_data_recieved"
QT_MOC_LITERAL(37, 497, 4), // "data"
QT_MOC_LITERAL(38, 502, 16), // "some_data_sended"
QT_MOC_LITERAL(39, 519, 12), // "displayError"
QT_MOC_LITERAL(40, 532, 12), // "on_connected"
QT_MOC_LITERAL(41, 545, 12) // "on_encrypted"

    },
    "ZPNetwork::zp_netTransThread\0evt_Message\0"
    "\0psource\0evt_SocketError\0senderSock\0"
    "erro\0extraData\0evt_NewClientConnected\0"
    "client\0ba\0evt_ClientEncrypted\0"
    "evt_ClientDisconnected\0evt_Data_recieved\0"
    "evt_Data_transferred\0incomingConnection\0"
    "threadid\0session\0startConnection\0"
    "QHostAddress\0addr\0port\0SendDataToClient\0"
    "objClient\0dtarray\0Deactivate\0"
    "DeactivateImmediately\0zp_netTransThread*\0"
    "KickAllClients\0KickClient\0"
    "KickRabishCanTimeOutObj\0AddNewClientOk\0"
    "pSock\0EmptyRabishCan\0pTransObj\0"
    "client_closed\0new_data_recieved\0data\0"
    "some_data_sended\0displayError\0"
    "on_connected\0on_encrypted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPNetwork__zp_netTransThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  129,    2, 0x06 /* Public */,
       4,    3,  134,    2, 0x06 /* Public */,
       8,    3,  141,    2, 0x06 /* Public */,
      11,    2,  148,    2, 0x06 /* Public */,
      12,    2,  153,    2, 0x06 /* Public */,
      13,    3,  158,    2, 0x06 /* Public */,
      14,    3,  165,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,  172,    2, 0x0a /* Public */,
      18,    4,  177,    2, 0x0a /* Public */,
      22,    2,  186,    2, 0x0a /* Public */,
      25,    0,  191,    2, 0x0a /* Public */,
      26,    1,  192,    2, 0x0a /* Public */,
      28,    1,  195,    2, 0x0a /* Public */,
      29,    1,  198,    2, 0x0a /* Public */,
      30,    0,  201,    2, 0x0a /* Public */,
      31,    1,  202,    2, 0x0a /* Public */,
      33,    1,  205,    2, 0x0a /* Public */,
      35,    0,  208,    2, 0x09 /* Protected */,
      36,    1,  209,    2, 0x09 /* Protected */,
      38,    1,  212,    2, 0x09 /* Protected */,
      39,    1,  215,    2, 0x09 /* Protected */,
      40,    0,  218,    2, 0x09 /* Protected */,
      41,    0,  219,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString, QMetaType::ULongLong,    5,    6,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray, QMetaType::ULongLong,    9,   10,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::ULongLong,    9,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::ULongLong,    9,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray, QMetaType::ULongLong,    2,    2,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::LongLong, QMetaType::ULongLong,    9,    2,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::VoidStar,   16,   17,
    QMetaType::Void, QMetaType::QObjectStar, 0x80000000 | 19, QMetaType::UShort, QMetaType::ULongLong,   16,   20,   21,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,   23,   24,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,    2,
    QMetaType::Void, 0x80000000 | 27,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   32,
    QMetaType::Void, QMetaType::QObjectStar,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   37,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZPNetwork::zp_netTransThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zp_netTransThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->evt_SocketError((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 2: _t->evt_NewClientConnected((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 3: _t->evt_ClientEncrypted((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 4: _t->evt_ClientDisconnected((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 5: _t->evt_Data_recieved((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 6: _t->evt_Data_transferred((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 7: _t->incomingConnection((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 8: _t->startConnection((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4]))); break;
        case 9: _t->SendDataToClient((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 10: _t->Deactivate(); break;
        case 11: _t->DeactivateImmediately((*reinterpret_cast< zp_netTransThread*(*)>(_a[1]))); break;
        case 12: _t->KickAllClients((*reinterpret_cast< zp_netTransThread*(*)>(_a[1]))); break;
        case 13: _t->KickClient((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 14: _t->KickRabishCanTimeOutObj(); break;
        case 15: _t->AddNewClientOk((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 16: _t->EmptyRabishCan((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 17: _t->client_closed(); break;
        case 18: _t->new_data_recieved((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 19: _t->some_data_sended((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 20: _t->displayError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->on_connected(); break;
        case 22: _t->on_encrypted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_netTransThread* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_netTransThread* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (zp_netTransThread::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_Message)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , const QString & , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_SocketError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , QByteArray , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_NewClientConnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_ClientEncrypted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_ClientDisconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , QByteArray , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_Data_recieved)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (zp_netTransThread::*)(QObject * , qint64 , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netTransThread::evt_Data_transferred)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZPNetwork::zp_netTransThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ZPNetwork__zp_netTransThread.data,
    qt_meta_data_ZPNetwork__zp_netTransThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZPNetwork::zp_netTransThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPNetwork::zp_netTransThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPNetwork__zp_netTransThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZPNetwork::zp_netTransThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void ZPNetwork::zp_netTransThread::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZPNetwork::zp_netTransThread::evt_SocketError(QObject * _t1, const QString & _t2, quint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZPNetwork::zp_netTransThread::evt_NewClientConnected(QObject * _t1, QByteArray _t2, quint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZPNetwork::zp_netTransThread::evt_ClientEncrypted(QObject * _t1, quint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZPNetwork::zp_netTransThread::evt_ClientDisconnected(QObject * _t1, quint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZPNetwork::zp_netTransThread::evt_Data_recieved(QObject * _t1, QByteArray _t2, quint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ZPNetwork::zp_netTransThread::evt_Data_transferred(QObject * _t1, qint64 _t2, quint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
