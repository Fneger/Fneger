/****************************************************************************
** Meta object code from reading C++ file 'st_client_event.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/smartlink/st_client_event.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_client_event.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BdUgdServer__st_client_event_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BdUgdServer__st_client_event_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BdUgdServer__st_client_event_t qt_meta_stringdata_BdUgdServer__st_client_event = {
    {
QT_MOC_LITERAL(0, 0, 28) // "BdUgdServer::st_client_event"

    },
    "BdUgdServer::st_client_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BdUgdServer__st_client_event[] = {

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

void BdUgdServer::st_client_event::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject BdUgdServer::st_client_event::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BdUgdServer__st_client_event.data,
    qt_meta_data_BdUgdServer__st_client_event,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BdUgdServer::st_client_event::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BdUgdServer::st_client_event::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BdUgdServer__st_client_event.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BdUgdServer::st_client_event::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
