/****************************************************************************
** Meta object code from reading C++ file 'st_clientnode_basetrans.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/smartlink/st_clientnode_basetrans.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_clientnode_basetrans.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans_t {
    QByteArrayData data[8];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans_t qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans = {
    {
QT_MOC_LITERAL(0, 0, 38), // "ExampleServer::st_clientNode_..."
QT_MOC_LITERAL(1, 39, 20), // "evt_SendDataToClient"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 9), // "objClient"
QT_MOC_LITERAL(4, 71, 7), // "dtarray"
QT_MOC_LITERAL(5, 79, 16), // "evt_close_client"
QT_MOC_LITERAL(6, 96, 11), // "evt_Message"
QT_MOC_LITERAL(7, 108, 7) // "psource"

    },
    "ExampleServer::st_clientNode_baseTrans\0"
    "evt_SendDataToClient\0\0objClient\0dtarray\0"
    "evt_close_client\0evt_Message\0psource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExampleServer__st_clientNode_baseTrans[] = {

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
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,
       6,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    7,    2,

       0        // eod
};

void ExampleServer::st_clientNode_baseTrans::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<st_clientNode_baseTrans *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_SendDataToClient((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->evt_close_client((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->evt_Message((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (st_clientNode_baseTrans::*)(QObject * , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_clientNode_baseTrans::evt_SendDataToClient)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (st_clientNode_baseTrans::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_clientNode_baseTrans::evt_close_client)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (st_clientNode_baseTrans::*)(QObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&st_clientNode_baseTrans::evt_Message)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExampleServer::st_clientNode_baseTrans::staticMetaObject = { {
    &ZPTaskEngine::zp_plTaskBase::staticMetaObject,
    qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans.data,
    qt_meta_data_ExampleServer__st_clientNode_baseTrans,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExampleServer::st_clientNode_baseTrans::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExampleServer::st_clientNode_baseTrans::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExampleServer__st_clientNode_baseTrans.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "BdUgdServer::st_client_protocol"))
        return static_cast< BdUgdServer::st_client_protocol*>(this);
    return ZPTaskEngine::zp_plTaskBase::qt_metacast(_clname);
}

int ExampleServer::st_clientNode_baseTrans::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZPTaskEngine::zp_plTaskBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ExampleServer::st_clientNode_baseTrans::evt_SendDataToClient(QObject * _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExampleServer::st_clientNode_baseTrans::evt_close_client(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExampleServer::st_clientNode_baseTrans::evt_Message(QObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
