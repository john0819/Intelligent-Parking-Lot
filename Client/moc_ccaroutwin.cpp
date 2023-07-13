/****************************************************************************
** Meta object code from reading C++ file 'ccaroutwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ccaroutwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccaroutwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCarOutWin_t {
    QByteArrayData data[19];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCarOutWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCarOutWin_t qt_meta_stringdata_CCarOutWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CCarOutWin"
QT_MOC_LITERAL(1, 11, 15), // "SendCurrentInfo"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "time_update"
QT_MOC_LITERAL(4, 40, 8), // "getFrame"
QT_MOC_LITERAL(5, 49, 3), // "Mat"
QT_MOC_LITERAL(6, 53, 5), // "frame"
QT_MOC_LITERAL(7, 59, 17), // "ChangeCurrentInfo"
QT_MOC_LITERAL(8, 77, 13), // "getCaroutInfo"
QT_MOC_LITERAL(9, 91, 4), // "flag"
QT_MOC_LITERAL(10, 96, 7), // "CAROUT&"
QT_MOC_LITERAL(11, 104, 3), // "car"
QT_MOC_LITERAL(12, 108, 8), // "getCarGo"
QT_MOC_LITERAL(13, 117, 12), // "getPictureOk"
QT_MOC_LITERAL(14, 130, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(15, 154, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(16, 176, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(17, 199, 7), // "checked"
QT_MOC_LITERAL(18, 207, 23) // "on_pushButton_3_clicked"

    },
    "CCarOutWin\0SendCurrentInfo\0\0time_update\0"
    "getFrame\0Mat\0frame\0ChangeCurrentInfo\0"
    "getCaroutInfo\0flag\0CAROUT&\0car\0getCarGo\0"
    "getPictureOk\0on_pushButton_2_clicked\0"
    "on_pushButton_clicked\0on_radioButton_clicked\0"
    "checked\0on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCarOutWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    2,   75,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,
      16,    1,   88,    2, 0x08 /* Private */,
      18,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void,

       0        // eod
};

void CCarOutWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCarOutWin *_t = static_cast<CCarOutWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendCurrentInfo(); break;
        case 1: _t->time_update(); break;
        case 2: _t->getFrame((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 3: _t->ChangeCurrentInfo(); break;
        case 4: _t->getCaroutInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CAROUT(*)>(_a[2]))); break;
        case 5: _t->getCarGo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->getPictureOk((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->on_radioButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CCarOutWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CCarOutWin::SendCurrentInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CCarOutWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CCarOutWin.data,
      qt_meta_data_CCarOutWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CCarOutWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCarOutWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CCarOutWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CCarOutWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void CCarOutWin::SendCurrentInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
