/****************************************************************************
** Meta object code from reading C++ file 'vcrreviewwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vcrreviewwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vcrreviewwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VCRReviewWin_t {
    QByteArrayData data[24];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VCRReviewWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VCRReviewWin_t qt_meta_stringdata_VCRReviewWin = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VCRReviewWin"
QT_MOC_LITERAL(1, 13, 11), // "getBigImage"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 43, 4), // "item"
QT_MOC_LITERAL(5, 48, 8), // "GetRatio"
QT_MOC_LITERAL(6, 57, 5), // "ratio"
QT_MOC_LITERAL(7, 63, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(8, 86, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(9, 111, 12), // "getMonthData"
QT_MOC_LITERAL(10, 124, 4), // "flag"
QT_MOC_LITERAL(11, 129, 14), // "vector<SEARCH>"
QT_MOC_LITERAL(12, 144, 6), // "search"
QT_MOC_LITERAL(13, 151, 10), // "getDayData"
QT_MOC_LITERAL(14, 162, 10), // "changeItem"
QT_MOC_LITERAL(15, 173, 13), // "getMonthVideo"
QT_MOC_LITERAL(16, 187, 17), // "vector<VIDEOINFO>"
QT_MOC_LITERAL(17, 205, 5), // "video"
QT_MOC_LITERAL(18, 211, 11), // "getDayVideo"
QT_MOC_LITERAL(19, 223, 11), // "getOneVideo"
QT_MOC_LITERAL(20, 235, 10), // "VIDEOINFO&"
QT_MOC_LITERAL(21, 246, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(22, 270, 12), // "getMoreMonth"
QT_MOC_LITERAL(23, 283, 11) // "getDayMonth"

    },
    "VCRReviewWin\0getBigImage\0\0QListWidgetItem*\0"
    "item\0GetRatio\0ratio\0on_radioButton_clicked\0"
    "on_radioButton_2_clicked\0getMonthData\0"
    "flag\0vector<SEARCH>\0search\0getDayData\0"
    "changeItem\0getMonthVideo\0vector<VIDEOINFO>\0"
    "video\0getDayVideo\0getOneVideo\0VIDEOINFO&\0"
    "on_pushButton_2_clicked\0getMoreMonth\0"
    "getDayMonth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VCRReviewWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       5,    1,   82,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    2,   87,    2, 0x08 /* Private */,
      13,    2,   92,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      15,    2,  100,    2, 0x08 /* Private */,
      18,    2,  105,    2, 0x08 /* Private */,
      19,    2,  110,    2, 0x08 /* Private */,
      21,    0,  115,    2, 0x08 /* Private */,
      22,    2,  116,    2, 0x08 /* Private */,
      23,    2,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   10,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   10,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 20,   10,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   10,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   10,   17,

       0        // eod
};

void VCRReviewWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VCRReviewWin *_t = static_cast<VCRReviewWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getBigImage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->GetRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_radioButton_clicked(); break;
        case 3: _t->on_radioButton_2_clicked(); break;
        case 4: _t->getMonthData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<SEARCH>(*)>(_a[2]))); break;
        case 5: _t->getDayData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<SEARCH>(*)>(_a[2]))); break;
        case 6: _t->changeItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->getMonthVideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<VIDEOINFO>(*)>(_a[2]))); break;
        case 8: _t->getDayVideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<VIDEOINFO>(*)>(_a[2]))); break;
        case 9: _t->getOneVideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< VIDEOINFO(*)>(_a[2]))); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->getMoreMonth((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<VIDEOINFO>(*)>(_a[2]))); break;
        case 12: _t->getDayMonth((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<VIDEOINFO>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject VCRReviewWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VCRReviewWin.data,
      qt_meta_data_VCRReviewWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VCRReviewWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VCRReviewWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VCRReviewWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VCRReviewWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
