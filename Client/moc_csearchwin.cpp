/****************************************************************************
** Meta object code from reading C++ file 'csearchwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "csearchwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'csearchwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CSearchWin_t {
    QByteArrayData data[15];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSearchWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSearchWin_t qt_meta_stringdata_CSearchWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CSearchWin"
QT_MOC_LITERAL(1, 11, 10), // "getClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "getClicked1"
QT_MOC_LITERAL(4, 35, 10), // "selectDate"
QT_MOC_LITERAL(5, 46, 4), // "data"
QT_MOC_LITERAL(6, 51, 11), // "selectDate1"
QT_MOC_LITERAL(7, 63, 11), // "getDataInfo"
QT_MOC_LITERAL(8, 75, 4), // "flag"
QT_MOC_LITERAL(9, 80, 13), // "vector<CINFO>"
QT_MOC_LITERAL(10, 94, 4), // "info"
QT_MOC_LITERAL(11, 99, 11), // "getMoreInfo"
QT_MOC_LITERAL(12, 111, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(13, 135, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(14, 157, 23) // "on_pushButton_4_clicked"

    },
    "CSearchWin\0getClicked\0\0getClicked1\0"
    "selectDate\0data\0selectDate1\0getDataInfo\0"
    "flag\0vector<CINFO>\0info\0getMoreInfo\0"
    "on_pushButton_2_clicked\0on_pushButton_clicked\0"
    "on_pushButton_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSearchWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       7,    2,   67,    2, 0x0a /* Public */,
      11,    2,   72,    2, 0x0a /* Public */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CSearchWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CSearchWin *_t = static_cast<CSearchWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getClicked(); break;
        case 1: _t->getClicked1(); break;
        case 2: _t->selectDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->selectDate1((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->getDataInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<CINFO>(*)>(_a[2]))); break;
        case 5: _t->getMoreInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<CINFO>(*)>(_a[2]))); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_pushButton_4_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject CSearchWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSearchWin.data,
      qt_meta_data_CSearchWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CSearchWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSearchWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CSearchWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CSearchWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
