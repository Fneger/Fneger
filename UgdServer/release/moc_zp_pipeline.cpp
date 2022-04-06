/****************************************************************************
** Meta object code from reading C++ file 'zp_pipeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZoomPipeline/pipeline/zp_pipeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zp_pipeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPTaskEngine__zp_pipeline_t {
    QByteArrayData data[10];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPTaskEngine__zp_pipeline_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPTaskEngine__zp_pipeline_t qt_meta_stringdata_ZPTaskEngine__zp_pipeline = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ZPTaskEngine::zp_pipeline"
QT_MOC_LITERAL(1, 26, 14), // "evt_start_work"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 19), // "zp_plWorkingThread*"
QT_MOC_LITERAL(4, 62, 4), // "task"
QT_MOC_LITERAL(5, 67, 13), // "evt_stop_work"
QT_MOC_LITERAL(6, 81, 16), // "on_finished_task"
QT_MOC_LITERAL(7, 98, 8), // "pushTask"
QT_MOC_LITERAL(8, 107, 14), // "zp_plTaskBase*"
QT_MOC_LITERAL(9, 122, 5) // "bFire"

    },
    "ZPTaskEngine::zp_pipeline\0evt_start_work\0"
    "\0zp_plWorkingThread*\0task\0evt_stop_work\0"
    "on_finished_task\0pushTask\0zp_plTaskBase*\0"
    "bFire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPTaskEngine__zp_pipeline[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x0a /* Public */,
       7,    2,   48,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool,    4,    9,
    QMetaType::Void, 0x80000000 | 8,    4,

       0        // eod
};

void ZPTaskEngine::zp_pipeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zp_pipeline *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_start_work((*reinterpret_cast< zp_plWorkingThread*(*)>(_a[1]))); break;
        case 1: _t->evt_stop_work((*reinterpret_cast< zp_plWorkingThread*(*)>(_a[1]))); break;
        case 2: _t->on_finished_task((*reinterpret_cast< zp_plWorkingThread*(*)>(_a[1]))); break;
        case 3: _t->pushTask((*reinterpret_cast< zp_plTaskBase*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->pushTask((*reinterpret_cast< zp_plTaskBase*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_plWorkingThread* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_plWorkingThread* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_plWorkingThread* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_plTaskBase* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< zp_plTaskBase* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (zp_pipeline::*)(zp_plWorkingThread * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_pipeline::evt_start_work)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (zp_pipeline::*)(zp_plWorkingThread * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&zp_pipeline::evt_stop_work)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZPTaskEngine::zp_pipeline::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ZPTaskEngine__zp_pipeline.data,
    qt_meta_data_ZPTaskEngine__zp_pipeline,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZPTaskEngine::zp_pipeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPTaskEngine::zp_pipeline::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPTaskEngine__zp_pipeline.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZPTaskEngine::zp_pipeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ZPTaskEngine::zp_pipeline::evt_start_work(zp_plWorkingThread * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZPTaskEngine::zp_pipeline::evt_stop_work(zp_plWorkingThread * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
