/****************************************************************************
** Meta object code from reading C++ file 'st_clientnode_applayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/smartlink/st_clientnode_applayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_clientnode_applayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer_t {
    QByteArrayData data[1];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer_t qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer = {
    {
QT_MOC_LITERAL(0, 0, 36) // "ExampleServer::st_clientNodeA..."

    },
    "ExampleServer::st_clientNodeAppLayer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExampleServer__st_clientNodeAppLayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ExampleServer::st_clientNodeAppLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ExampleServer::st_clientNodeAppLayer::staticMetaObject = { {
    &st_clientNode_baseTrans::staticMetaObject,
    qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer.data,
    qt_meta_data_ExampleServer__st_clientNodeAppLayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExampleServer::st_clientNodeAppLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExampleServer::st_clientNodeAppLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExampleServer__st_clientNodeAppLayer.stringdata0))
        return static_cast<void*>(this);
    return st_clientNode_baseTrans::qt_metacast(_clname);
}

int ExampleServer::st_clientNodeAppLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = st_clientNode_baseTrans::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
