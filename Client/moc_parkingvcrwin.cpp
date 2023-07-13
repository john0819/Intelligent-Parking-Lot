/****************************************************************************
** Meta object code from reading C++ file 'parkingvcrwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "parkingvcrwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parkingvcrwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParkingVCRWin_t {
    QByteArrayData data[16];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParkingVCRWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParkingVCRWin_t qt_meta_stringdata_ParkingVCRWin = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ParkingVCRWin"
QT_MOC_LITERAL(1, 14, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "updateImage"
QT_MOC_LITERAL(4, 49, 3), // "Mat"
QT_MOC_LITERAL(5, 53, 5), // "frame"
QT_MOC_LITERAL(6, 59, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(7, 83, 17), // "CreateMutualVideo"
QT_MOC_LITERAL(8, 101, 15), // "CreateAutoVideo"
QT_MOC_LITERAL(9, 117, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(10, 137, 7), // "checked"
QT_MOC_LITERAL(11, 145, 11), // "getParkInfo"
QT_MOC_LITERAL(12, 157, 4), // "flag"
QT_MOC_LITERAL(13, 162, 9), // "PARKINFO&"
QT_MOC_LITERAL(14, 172, 4), // "park"
QT_MOC_LITERAL(15, 177, 14) // "getVideoRecord"

    },
    "ParkingVCRWin\0on_pushButton_clicked\0"
    "\0updateImage\0Mat\0frame\0on_pushButton_2_clicked\0"
    "CreateMutualVideo\0CreateAutoVideo\0"
    "on_checkBox_clicked\0checked\0getParkInfo\0"
    "flag\0PARKINFO&\0park\0getVideoRecord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParkingVCRWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    1,   55,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    1,   61,    2, 0x08 /* Private */,
      11,    2,   64,    2, 0x08 /* Private */,
      15,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void ParkingVCRWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParkingVCRWin *_t = static_cast<ParkingVCRWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->updateImage((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->CreateMutualVideo(); break;
        case 4: _t->CreateAutoVideo(); break;
        case 5: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->getParkInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< PARKINFO(*)>(_a[2]))); break;
        case 7: _t->getVideoRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ParkingVCRWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ParkingVCRWin.data,
      qt_meta_data_ParkingVCRWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ParkingVCRWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParkingVCRWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParkingVCRWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ParkingVCRWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
