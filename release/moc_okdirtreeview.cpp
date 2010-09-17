/****************************************************************************
** Meta object code from reading C++ file 'okdirtreeview.h'
**
** Created: Mon 6. Sep 01:04:43 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okWidgets/okdirtreeview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okdirtreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okDirTreeView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      41,   15,   14,   14, 0x05,
      66,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_okDirTreeView[] = {
    "okDirTreeView\0\0i\0midClicked(QModelIndex)\0"
    "newPlaylist(QModelIndex)\0"
    "addToPlaylist(QModelIndex)\0"
};

const QMetaObject okDirTreeView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_okDirTreeView,
      qt_meta_data_okDirTreeView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okDirTreeView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okDirTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okDirTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okDirTreeView))
        return static_cast<void*>(const_cast< okDirTreeView*>(this));
    return QTreeView::qt_metacast(_clname);
}

int okDirTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: midClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: newPlaylist((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: addToPlaylist((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void okDirTreeView::midClicked(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void okDirTreeView::newPlaylist(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void okDirTreeView::addToPlaylist(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
