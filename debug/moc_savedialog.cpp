/****************************************************************************
** Meta object code from reading C++ file 'savedialog.h'
**
** Created: Wed 8. Sep 00:05:34 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../savedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'savedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_savedialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   32,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_savedialog[] = {
    "savedialog\0\0checkIfCanBeSaved()\0text\0"
    "checkIfCanBeSaved(QString)\0"
};

const QMetaObject savedialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_savedialog,
      qt_meta_data_savedialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &savedialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *savedialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *savedialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_savedialog))
        return static_cast<void*>(const_cast< savedialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int savedialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkIfCanBeSaved(); break;
        case 1: checkIfCanBeSaved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
