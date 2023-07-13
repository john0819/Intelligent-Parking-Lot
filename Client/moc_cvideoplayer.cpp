/****************************************************************************
** Meta object code from reading C++ file 'cvideoplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cvideoplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cvideoplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CVideoPlayer_t {
    QByteArrayData data[15];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVideoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVideoPlayer_t qt_meta_stringdata_CVideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CVideoPlayer"
QT_MOC_LITERAL(1, 13, 10), // "changeFlag"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "sendValue"
QT_MOC_LITERAL(4, 35, 5), // "value"
QT_MOC_LITERAL(5, 41, 9), // "sendRatio"
QT_MOC_LITERAL(6, 51, 3), // "str"
QT_MOC_LITERAL(7, 55, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(8, 77, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(9, 110, 8), // "getFrame"
QT_MOC_LITERAL(10, 119, 3), // "Mat"
QT_MOC_LITERAL(11, 123, 5), // "frame"
QT_MOC_LITERAL(12, 129, 3), // "num"
QT_MOC_LITERAL(13, 133, 8), // "getCount"
QT_MOC_LITERAL(14, 142, 5) // "count"

    },
    "CVideoPlayer\0changeFlag\0\0sendValue\0"
    "value\0sendRatio\0str\0on_pushButton_clicked\0"
    "on_horizontalSlider_valueChanged\0"
    "getFrame\0Mat\0frame\0num\0getCount\0count"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVideoPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   56,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,
       9,    2,   60,    2, 0x08 /* Private */,
      13,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Double,   14,

       0        // eod
};

void CVideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVideoPlayer *_t = static_cast<CVideoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeFlag(); break;
        case 1: _t->sendValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->getFrame((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->getCount((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CVideoPlayer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoPlayer::changeFlag)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CVideoPlayer::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoPlayer::sendValue)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CVideoPlayer::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoPlayer::sendRatio)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CVideoPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CVideoPlayer.data,
      qt_meta_data_CVideoPlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CVideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CVideoPlayer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CVideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CVideoPlayer::changeFlag()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CVideoPlayer::sendValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CVideoPlayer::sendRatio(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
