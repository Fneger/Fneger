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
    QByteArrayData data[13];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPMainFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPMainFrame_t qt_meta_stringdata_ZPMainFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ZPMainFrame"
QT_MOC_LITERAL(1, 12, 21), // "on_evt_MessageNetwork"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "psource"
QT_MOC_LITERAL(4, 43, 18), // "on_evt_SocketError"
QT_MOC_LITERAL(5, 62, 10), // "senderSock"
QT_MOC_LITERAL(6, 73, 4), // "erro"
QT_MOC_LITERAL(7, 78, 22), // "on_evt_Message_Cluster"
QT_MOC_LITERAL(8, 101, 23), // "on_evt_Message_Database"
QT_MOC_LITERAL(9, 125, 24), // "on_evt_Message_Smartlink"
QT_MOC_LITERAL(10, 150, 26), // "on_evt_SocketError_Cluster"
QT_MOC_LITERAL(11, 177, 30), // "on_actionShow_Window_triggered"
QT_MOC_LITERAL(12, 208, 23) // "on_actionExit_triggered"

    },
    "ZPMainFrame\0on_evt_MessageNetwork\0\0"
    "psource\0on_evt_SocketError\0senderSock\0"
    "erro\0on_evt_Message_Cluster\0"
    "on_evt_Message_Database\0"
    "on_evt_Message_Smartlink\0"
    "on_evt_SocketError_Cluster\0"
    "on_actionShow_Window_triggered\0"
    "on_actionExit_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPMainFrame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x0a /* Public */,
       4,    2,   59,    2, 0x0a /* Public */,
       7,    2,   64,    2, 0x0a /* Public */,
       8,    2,   69,    2, 0x0a /* Public */,
       9,    2,   74,    2, 0x0a /* Public */,
      10,    2,   79,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    2,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    5,    6,
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
        case 0: _t->on_evt_MessageNetwork((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->on_evt_SocketError((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->on_evt_Message_Cluster((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->on_evt_Message_Database((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->on_evt_Message_Smartlink((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->on_evt_SocketError_Cluster((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->on_actionShow_Window_triggered(); break;
        case 7: _t->on_actionExit_triggered(); break;
        default: ;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
