/****************************************************************************
** Meta object code from reading C++ file 'casiotcpsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/asio/casiotcpsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'casiotcpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CAsioTcpSocket_t {
    QByteArrayData data[28];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAsioTcpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAsioTcpSocket_t qt_meta_stringdata_CAsioTcpSocket = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CAsioTcpSocket"
QT_MOC_LITERAL(1, 15, 13), // "connectToHost"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "hostName"
QT_MOC_LITERAL(4, 39, 4), // "port"
QT_MOC_LITERAL(5, 44, 18), // "disconnectFromHost"
QT_MOC_LITERAL(6, 63, 15), // "setSocketOption"
QT_MOC_LITERAL(7, 79, 32), // "CTcpAbstractSocket::SocketOption"
QT_MOC_LITERAL(8, 112, 6), // "option"
QT_MOC_LITERAL(9, 119, 7), // "isEnble"
QT_MOC_LITERAL(10, 127, 5), // "value"
QT_MOC_LITERAL(11, 133, 15), // "getSocketOption"
QT_MOC_LITERAL(12, 149, 19), // "std::pair<bool,int>"
QT_MOC_LITERAL(13, 169, 8), // "opention"
QT_MOC_LITERAL(14, 178, 8), // "do_start"
QT_MOC_LITERAL(15, 187, 26), // "resizeClientBackThreadSize"
QT_MOC_LITERAL(16, 214, 4), // "size"
QT_MOC_LITERAL(17, 219, 14), // "setIsNewClient"
QT_MOC_LITERAL(18, 234, 6), // "bIsNew"
QT_MOC_LITERAL(19, 241, 11), // "isNewClient"
QT_MOC_LITERAL(20, 253, 10), // "activeTime"
QT_MOC_LITERAL(21, 264, 13), // "setActiveTime"
QT_MOC_LITERAL(22, 278, 5), // "nTime"
QT_MOC_LITERAL(23, 284, 7), // "session"
QT_MOC_LITERAL(24, 292, 15), // "CSocketSession*"
QT_MOC_LITERAL(25, 308, 8), // "sendData"
QT_MOC_LITERAL(26, 317, 11), // "const char*"
QT_MOC_LITERAL(27, 329, 4) // "data"

    },
    "CAsioTcpSocket\0connectToHost\0\0hostName\0"
    "port\0disconnectFromHost\0setSocketOption\0"
    "CTcpAbstractSocket::SocketOption\0"
    "option\0isEnble\0value\0getSocketOption\0"
    "std::pair<bool,int>\0opention\0do_start\0"
    "resizeClientBackThreadSize\0size\0"
    "setIsNewClient\0bIsNew\0isNewClient\0"
    "activeTime\0setActiveTime\0nTime\0session\0"
    "CSocketSession*\0sendData\0const char*\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAsioTcpSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       5,    0,   79,    2, 0x0a /* Public */,
       6,    3,   80,    2, 0x0a /* Public */,
      11,    1,   87,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    1,   91,    2, 0x0a /* Public */,
      17,    1,   94,    2, 0x0a /* Public */,
      19,    0,   97,    2, 0x0a /* Public */,
      20,    0,   98,    2, 0x0a /* Public */,
      21,    1,   99,    2, 0x0a /* Public */,
      23,    0,  102,    2, 0x0a /* Public */,
      25,    2,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool, QMetaType::UInt,    8,    9,   10,
    0x80000000 | 12, 0x80000000 | 7,   13,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Bool,
    QMetaType::LongLong,
    QMetaType::Void, QMetaType::LongLong,   22,
    0x80000000 | 24,
    QMetaType::Void, 0x80000000 | 26, QMetaType::Int,   27,   16,

       0        // eod
};

void CAsioTcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CAsioTcpSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 1: _t->disconnectFromHost(); break;
        case 2: _t->setSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 3: { std::pair<bool,int> _r = _t->getSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::pair<bool,int>*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->do_start(); break;
        case 5: { int _r = _t->resizeClientBackThreadSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->setIsNewClient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: { bool _r = _t->isNewClient();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { qint64 _r = _t->activeTime();
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setActiveTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: { CSocketSession* _r = _t->session();
            if (_a[0]) *reinterpret_cast< CSocketSession**>(_a[0]) = std::move(_r); }  break;
        case 11: _t->sendData((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CAsioTcpSocket::staticMetaObject = { {
    &CTcpAbstractSocket::staticMetaObject,
    qt_meta_stringdata_CAsioTcpSocket.data,
    qt_meta_data_CAsioTcpSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CAsioTcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAsioTcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CAsioTcpSocket.stringdata0))
        return static_cast<void*>(this);
    return CTcpAbstractSocket::qt_metacast(_clname);
}

int CAsioTcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CTcpAbstractSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
