/****************************************************************************
** Meta object code from reading C++ file 'okplaylistlistwidget.h'
**
** Created: Mon 6. Sep 01:04:46 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okWidgets/okplaylistlistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okplaylistlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okPlaylistListWidget[] = {

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
      22,   21,   21,   21, 0x0a,
      37,   35,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_okPlaylistListWidget[] = {
    "okPlaylistListWidget\0\0updateList()\0i\0"
    "removePlaylist(QModelIndex)\0"
};

const QMetaObject okPlaylistListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_okPlaylistListWidget,
      qt_meta_data_okPlaylistListWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okPlaylistListWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okPlaylistListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okPlaylistListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okPlaylistListWidget))
        return static_cast<void*>(const_cast< okPlaylistListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int okPlaylistListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateList(); break;
        case 1: removePlaylist((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
