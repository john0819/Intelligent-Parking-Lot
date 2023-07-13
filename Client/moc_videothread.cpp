/****************************************************************************
** Meta object code from reading C++ file 'videothread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "videothread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videothread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoThread_t {
    QByteArrayData data[13];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoThread_t qt_meta_stringdata_VideoThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoThread"
QT_MOC_LITERAL(1, 12, 13), // "sendFrame2Win"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "Mat"
QT_MOC_LITERAL(4, 31, 5), // "frame"
QT_MOC_LITERAL(5, 37, 3), // "num"
QT_MOC_LITERAL(6, 41, 14), // "send2Win_Count"
QT_MOC_LITERAL(7, 56, 5), // "count"
QT_MOC_LITERAL(8, 62, 7), // "getFlag"
QT_MOC_LITERAL(9, 70, 8), // "getValue"
QT_MOC_LITERAL(10, 79, 5), // "value"
QT_MOC_LITERAL(11, 85, 8), // "getSpeed"
QT_MOC_LITERAL(12, 94, 5) // "speed"

    },
    "VideoThread\0sendFrame2Win\0\0Mat\0frame\0"
    "num\0send2Win_Count\0count\0getFlag\0"
    "getValue\0value\0getSpeed\0speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       6,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   47,    2, 0x0a /* Public */,
       9,    1,   48,    2, 0x0a /* Public */,
      11,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Double,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void VideoThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoThread *_t = static_cast<VideoThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendFrame2Win((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->send2Win_Count((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->getFlag(); break;
        case 3: _t->getValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->getSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (VideoThread::*_t)(Mat , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::sendFrame2Win)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VideoThread::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoThread::send2Win_Count)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject VideoThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VideoThread.data,
      qt_meta_data_VideoThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int VideoThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VideoThread::sendFrame2Win(Mat _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoThread::send2Win_Count(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
