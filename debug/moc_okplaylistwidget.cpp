/****************************************************************************
** Meta object code from reading C++ file 'okplaylistwidget.h'
**
** Created: Thu 9. Sep 19:11:41 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okWidgets/okplaylistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okplaylistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okPlaylistWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x05,
      54,   44,   17,   17, 0x05,
      82,   77,   17,   17, 0x05,
     112,   77,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     143,   18,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_okPlaylistWidget[] = {
    "okPlaylistWidget\0\0i\0midClicked(QModelIndex)\0"
    "trackPath\0trackSelected(QString)\0path\0"
    "droppedMediaToAppend(QString)\0"
    "droppedMediaToReplace(QString)\0"
    "emitTrackSelected(QModelIndex)\0"
};

const QMetaObject okPlaylistWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_okPlaylistWidget,
      qt_meta_data_okPlaylistWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okPlaylistWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okPlaylistWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okPlaylistWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okPlaylistWidget))
        return static_cast<void*>(const_cast< okPlaylistWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int okPlaylistWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: midClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: trackSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: droppedMediaToAppend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: droppedMediaToReplace((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: emitTrackSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void okPlaylistWidget::midClicked(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void okPlaylistWidget::trackSelected(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void okPlaylistWidget::droppedMediaToAppend(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void okPlaylistWidget::droppedMediaToReplace(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
