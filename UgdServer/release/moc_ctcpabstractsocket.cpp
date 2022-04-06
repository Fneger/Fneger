/****************************************************************************
** Meta object code from reading C++ file 'ctcpabstractsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/asio/ctcpabstractsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctcpabstractsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CTcpAbstractSocket_t {
    QByteArrayData data[26];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTcpAbstractSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTcpAbstractSocket_t qt_meta_stringdata_CTcpAbstractSocket = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CTcpAbstractSocket"
QT_MOC_LITERAL(1, 19, 9), // "connected"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "disConnected"
QT_MOC_LITERAL(4, 43, 11), // "stateChange"
QT_MOC_LITERAL(5, 55, 12), // "sentReadData"
QT_MOC_LITERAL(6, 68, 4), // "data"
QT_MOC_LITERAL(7, 73, 10), // "erroString"
QT_MOC_LITERAL(8, 84, 4), // "erro"
QT_MOC_LITERAL(9, 89, 10), // "hostFinded"
QT_MOC_LITERAL(10, 100, 12), // "bytesWritten"
QT_MOC_LITERAL(11, 113, 5), // "bytes"
QT_MOC_LITERAL(12, 119, 13), // "connectToHost"
QT_MOC_LITERAL(13, 133, 8), // "hostName"
QT_MOC_LITERAL(14, 142, 4), // "port"
QT_MOC_LITERAL(15, 147, 18), // "disconnectFromHost"
QT_MOC_LITERAL(16, 166, 5), // "write"
QT_MOC_LITERAL(17, 172, 11), // "const char*"
QT_MOC_LITERAL(18, 184, 4), // "size"
QT_MOC_LITERAL(19, 189, 15), // "setSocketOption"
QT_MOC_LITERAL(20, 205, 32), // "CTcpAbstractSocket::SocketOption"
QT_MOC_LITERAL(21, 238, 6), // "option"
QT_MOC_LITERAL(22, 245, 7), // "isEnble"
QT_MOC_LITERAL(23, 253, 5), // "value"
QT_MOC_LITERAL(24, 259, 15), // "getSocketOption"
QT_MOC_LITERAL(25, 275, 19) // "std::pair<bool,int>"

    },
    "CTcpAbstractSocket\0connected\0\0"
    "disConnected\0stateChange\0sentReadData\0"
    "data\0erroString\0erro\0hostFinded\0"
    "bytesWritten\0bytes\0connectToHost\0"
    "hostName\0port\0disconnectFromHost\0write\0"
    "const char*\0size\0setSocketOption\0"
    "CTcpAbstractSocket::SocketOption\0"
    "option\0isEnble\0value\0getSocketOption\0"
    "std::pair<bool,int>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTcpAbstractSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    1,   96,    2, 0x06 /* Public */,
       5,    1,   99,    2, 0x06 /* Public */,
       7,    1,  102,    2, 0x06 /* Public */,
       9,    0,  105,    2, 0x06 /* Public */,
      10,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,  109,    2, 0x0a /* Public */,
      15,    0,  114,    2, 0x0a /* Public */,
      16,    1,  115,    2, 0x0a /* Public */,
      16,    2,  118,    2, 0x0a /* Public */,
      16,    1,  123,    2, 0x2a /* Public | MethodCloned */,
      19,    3,  126,    2, 0x0a /* Public */,
      24,    1,  133,    2, 0x0a /* Public */,
      19,    2,  136,    2, 0x0a /* Public */,
      19,    2,  141,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,    6,   18,
    QMetaType::Void, 0x80000000 | 17,    6,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Bool, QMetaType::UInt,   21,   22,   23,
    0x80000000 | 25, 0x80000000 | 20,    2,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Bool,   21,   22,
    QMetaType::Void, 0x80000000 | 20, QMetaType::UInt,   21,   23,

       0        // eod
};

void CTcpAbstractSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CTcpAbstractSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disConnected(); break;
        case 2: _t->stateChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sentReadData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->erroString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->hostFinded(); break;
        case 6: _t->bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 8: _t->disconnectFromHost(); break;
        case 9: _t->write((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 10: _t->write((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->write((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 12: _t->setSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 13: { std::pair<bool,int> _r = _t->getSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::pair<bool,int>*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->setSocketOption((*reinterpret_cast< CTcpAbstractSocket::SocketOption(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CTcpAbstractSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::disConnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::stateChange)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::sentReadData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::erroString)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::hostFinded)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CTcpAbstractSocket::*)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTcpAbstractSocket::bytesWritten)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CTcpAbstractSocket::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CTcpAbstractSocket.data,
    qt_meta_data_CTcpAbstractSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CTcpAbstractSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTcpAbstractSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CTcpAbstractSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CTcpAbstractSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CTcpAbstractSocket::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CTcpAbstractSocket::disConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CTcpAbstractSocket::stateChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CTcpAbstractSocket::sentReadData(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CTcpAbstractSocket::erroString(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CTcpAbstractSocket::hostFinded()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CTcpAbstractSocket::bytesWritten(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
