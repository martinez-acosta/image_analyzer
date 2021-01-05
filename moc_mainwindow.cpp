/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "openImage"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "saveImageAs"
QT_MOC_LITERAL(4, 34, 15), // "duplicateWindow"
QT_MOC_LITERAL(5, 50, 9), // "grayscale"
QT_MOC_LITERAL(6, 60, 5), // "trans"
QT_MOC_LITERAL(7, 66, 7), // "mascara"
QT_MOC_LITERAL(8, 74, 11), // "convolution"
QT_MOC_LITERAL(9, 86, 5), // "opSum"
QT_MOC_LITERAL(10, 92, 6), // "opDiff"
QT_MOC_LITERAL(11, 99, 9), // "opProduct"
QT_MOC_LITERAL(12, 109, 5), // "opMin"
QT_MOC_LITERAL(13, 115, 5), // "opMax"
QT_MOC_LITERAL(14, 121, 12), // "opComplement"
QT_MOC_LITERAL(15, 134, 10), // "firstImage"
QT_MOC_LITERAL(16, 145, 17), // "ApplyThresholding"
QT_MOC_LITERAL(17, 163, 22), // "ApplyThresholdingValue"
QT_MOC_LITERAL(18, 186, 18), // "calculateHistogram"
QT_MOC_LITERAL(19, 205, 14), // "labelingNormal"
QT_MOC_LITERAL(20, 220, 13) // "labelingValue"

    },
    "MainWindow\0openImage\0\0saveImageAs\0"
    "duplicateWindow\0grayscale\0trans\0mascara\0"
    "convolution\0opSum\0opDiff\0opProduct\0"
    "opMin\0opMax\0opComplement\0firstImage\0"
    "ApplyThresholding\0ApplyThresholdingValue\0"
    "calculateHistogram\0labelingNormal\0"
    "labelingValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x08 /* Private */,
       3,    0,  110,    2, 0x08 /* Private */,
       4,    0,  111,    2, 0x08 /* Private */,
       5,    0,  112,    2, 0x08 /* Private */,
       6,    0,  113,    2, 0x08 /* Private */,
       7,    0,  114,    2, 0x08 /* Private */,
       8,    0,  115,    2, 0x08 /* Private */,
       9,    0,  116,    2, 0x08 /* Private */,
      10,    0,  117,    2, 0x08 /* Private */,
      11,    0,  118,    2, 0x08 /* Private */,
      12,    0,  119,    2, 0x08 /* Private */,
      13,    0,  120,    2, 0x08 /* Private */,
      14,    0,  121,    2, 0x08 /* Private */,
      15,    0,  122,    2, 0x08 /* Private */,
      16,    0,  123,    2, 0x08 /* Private */,
      17,    0,  124,    2, 0x08 /* Private */,
      18,    0,  125,    2, 0x08 /* Private */,
      19,    0,  126,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openImage(); break;
        case 1: _t->saveImageAs(); break;
        case 2: _t->duplicateWindow(); break;
        case 3: _t->grayscale(); break;
        case 4: _t->trans(); break;
        case 5: _t->mascara(); break;
        case 6: _t->convolution(); break;
        case 7: _t->opSum(); break;
        case 8: _t->opDiff(); break;
        case 9: _t->opProduct(); break;
        case 10: _t->opMin(); break;
        case 11: _t->opMax(); break;
        case 12: _t->opComplement(); break;
        case 13: _t->firstImage(); break;
        case 14: _t->ApplyThresholding(); break;
        case 15: _t->ApplyThresholdingValue(); break;
        case 16: _t->calculateHistogram(); break;
        case 17: _t->labelingNormal(); break;
        case 18: _t->labelingValue(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
