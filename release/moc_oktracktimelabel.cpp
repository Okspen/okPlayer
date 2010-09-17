/****************************************************************************
** Meta object code from reading C++ file 'oktracktimelabel.h'
**
** Created: Mon 6. Sep 01:04:40 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okWidgets/oktracktimelabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oktracktimelabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okTrackTimeLabel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_okTrackTimeLabel[] = {
    "okTrackTimeLabel\0\0updateTime()\0"
};

const QMetaObject okTrackTimeLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_okTrackTimeLabel,
      qt_meta_data_okTrackTimeLabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okTrackTimeLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okTrackTimeLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okTrackTimeLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okTrackTimeLabel))
        return static_cast<void*>(const_cast< okTrackTimeLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int okTrackTimeLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTime(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
