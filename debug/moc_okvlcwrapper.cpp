/****************************************************************************
** Meta object code from reading C++ file 'okvlcwrapper.h'
**
** Created: Wed 8. Sep 00:05:24 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okvlcwrapper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okvlcwrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okVLCWrapper[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      21,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   13,   13,   13, 0x0a,
      40,   13,   13,   13, 0x0a,
      47,   13,   13,   13, 0x0a,
      61,   54,   13,   13, 0x0a,
      83,   76,   13,   13, 0x0a,
     100,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_okVLCWrapper[] = {
    "okVLCWrapper\0\0tick()\0finished()\0pause()\0"
    "play()\0stop()\0newVol\0setVolume(int)\0"
    "newPos\0setPosition(int)\0emitTick()\0"
};

const QMetaObject okVLCWrapper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_okVLCWrapper,
      qt_meta_data_okVLCWrapper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okVLCWrapper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okVLCWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okVLCWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okVLCWrapper))
        return static_cast<void*>(const_cast< okVLCWrapper*>(this));
    return QObject::qt_metacast(_clname);
}

int okVLCWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tick(); break;
        case 1: finished(); break;
        case 2: pause(); break;
        case 3: play(); break;
        case 4: stop(); break;
        case 5: setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: emitTick(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void okVLCWrapper::tick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void okVLCWrapper::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
