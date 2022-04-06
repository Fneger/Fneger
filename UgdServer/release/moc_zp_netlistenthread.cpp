/****************************************************************************
** Meta object code from reading C++ file 'zp_netlistenthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/network/zp_netlistenthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_netlistenthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPNetwork__zp_netListenThread_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPNetwork__zp_netListenThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPNetwork__zp_netListenThread_t qt_meta_stringdata_ZPNetwork__zp_netListenThread = {
    {
QT_MOC_LITERAL(0, 0, 29), // "ZPNetwork::zp_netListenThread"
QT_MOC_LITERAL(1, 30, 11), // "evt_Message"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 16), // "evt_ListenClosed"
QT_MOC_LITERAL(4, 60, 20), // "evt_NewClientArrived"
QT_MOC_LITERAL(5, 81, 7), // "session"
QT_MOC_LITERAL(6, 89, 11), // "startListen"
QT_MOC_LITERAL(7, 101, 2), // "id"
QT_MOC_LITERAL(8, 104, 10) // "stopListen"

    },
    "ZPNetwork::zp_netListenThread\0evt_Message\0"
    "\0evt_ListenClosed\0evt_NewClientArrived\0"
    "session\0startListen\0id\0stopListen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPNetwork__zp_netListenThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       3,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::VoidStar,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void ZPNetwork::zp_netListenThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zp_netListenThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->evt_ListenClosed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->evt_NewClientArrived((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 3: _t->startListen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->stopListen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (zp_netListenThread::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netListenThread::evt_Message)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (zp_netListenThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netListenThread::evt_ListenClosed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (zp_netListenThread::*)(void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_netListenThread::evt_NewClientArrived)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZPNetwork::zp_netListenThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ZPNetwork__zp_netListenThread.data,
    qt_meta_data_ZPNetwork__zp_netListenThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZPNetwork::zp_netListenThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPNetwork::zp_netListenThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPNetwork__zp_netListenThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZPNetwork::zp_netListenThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ZPNetwork::zp_netListenThread::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZPNetwork::zp_netListenThread::evt_ListenClosed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZPNetwork::zp_netListenThread::evt_NewClientArrived(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
