/****************************************************************************
** Meta object code from reading C++ file 'zpmainframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../zpmainframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zpmainframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPMainFrame_t {
    QByteArrayData data[16];
    char stringdata0[309];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPMainFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPMainFrame_t qt_meta_stringdata_ZPMainFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ZPMainFrame"
QT_MOC_LITERAL(1, 12, 19), // "evt_KickDeadClients"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "evt_CleanNoActiveNode"
QT_MOC_LITERAL(4, 55, 18), // "evt_CleanDeadNodes"
QT_MOC_LITERAL(5, 74, 23), // "slot_evt_MessageNetwork"
QT_MOC_LITERAL(6, 98, 7), // "psource"
QT_MOC_LITERAL(7, 106, 20), // "slot_evt_SocketError"
QT_MOC_LITERAL(8, 127, 10), // "senderSock"
QT_MOC_LITERAL(9, 138, 4), // "erro"
QT_MOC_LITERAL(10, 143, 24), // "slot_evt_Message_Cluster"
QT_MOC_LITERAL(11, 168, 25), // "slot_evt_Message_Database"
QT_MOC_LITERAL(12, 194, 26), // "slot_evt_Message_Smartlink"
QT_MOC_LITERAL(13, 221, 28), // "slot_evt_SocketError_Cluster"
QT_MOC_LITERAL(14, 250, 32), // "slot_actionShow_Window_triggered"
QT_MOC_LITERAL(15, 283, 25) // "slot_actionExit_triggered"

    },
    "ZPMainFrame\0evt_KickDeadClients\0\0"
    "evt_CleanNoActiveNode\0evt_CleanDeadNodes\0"
    "slot_evt_MessageNetwork\0psource\0"
    "slot_evt_SocketError\0senderSock\0erro\0"
    "slot_evt_Message_Cluster\0"
    "slot_evt_Message_Database\0"
    "slot_evt_Message_Smartlink\0"
    "slot_evt_SocketError_Cluster\0"
    "slot_actionShow_Window_triggered\0"
    "slot_actionExit_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPMainFrame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   72,    2, 0x0a /* Public */,
       7,    2,   77,    2, 0x0a /* Public */,
      10,    2,   82,    2, 0x0a /* Public */,
      11,    2,   87,    2, 0x0a /* Public */,
      12,    2,   92,    2, 0x0a /* Public */,
      13,    2,   97,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    6,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    6,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    6,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    6,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZPMainFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ZPMainFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evt_KickDeadClients(); break;
        case 1: _t->evt_CleanNoActiveNode(); break;
        case 2: _t->evt_CleanDeadNodes(); break;
        case 3: _t->slot_evt_MessageNetwork((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->slot_evt_SocketError((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->slot_evt_Message_Cluster((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->slot_evt_Message_Database((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->slot_evt_Message_Smartlink((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->slot_evt_SocketError_Cluster((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->slot_actionShow_Window_triggered(); break;
        case 10: _t->slot_actionExit_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ZPMainFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZPMainFrame::evt_KickDeadClients)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ZPMainFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZPMainFrame::evt_CleanNoActiveNode)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ZPMainFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZPMainFrame::evt_CleanDeadNodes)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ZPMainFrame::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ZPMainFrame.data,
    qt_meta_data_ZPMainFrame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ZPMainFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPMainFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPMainFrame.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ZPMainFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ZPMainFrame::evt_KickDeadClients()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ZPMainFrame::evt_CleanNoActiveNode()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ZPMainFrame::evt_CleanDeadNodes()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
