/****************************************************************************
** Meta object code from reading C++ file 'okplayer.h'
**
** Created: Mon 6. Sep 01:04:36 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../okplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_okPlayer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   43,    9,    9, 0x0a,
      60,    9,    9,    9, 0x0a,
      67,    9,    9,    9, 0x0a,
      75,    9,    9,    9, 0x0a,
      86,   82,    9,    9, 0x0a,
     105,   96,    9,    9, 0x0a,
     119,    9,    9,    9, 0x0a,
     132,    9,    9,    9, 0x0a,
     146,    9,    9,    9, 0x0a,
     153,    9,    9,    9, 0x0a,
     160,    9,    9,    9, 0x0a,
     173,  171,    9,    9, 0x0a,
     207,   96,    9,    9, 0x0a,
     241,  236,    9,    9, 0x0a,
     270,  171,    9,    9, 0x0a,
     306,    9,    9,    9, 0x0a,
     332,   96,    9,    9, 0x0a,
     363,  236,    9,    9, 0x0a,
     394,    9,    9,    9, 0x0a,
     421,  415,    9,    9, 0x0a,
     447,  442,    9,    9, 0x0a,
     490,  486,    9,    9, 0x0a,
     532,  523,    9,    9, 0x0a,
     557,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_okPlayer[] = {
    "okPlayer\0\0newStatus\0statusChanged(QString)\0"
    "v\0setVolume(int)\0stop()\0pause()\0play()\0"
    "num\0play(int)\0fileName\0play(QString)\0"
    "playRandom()\0playCurrent()\0prev()\0"
    "next()\0nextAuto()\0i\0"
    "newPlaylistFromIndex(QModelIndex)\0"
    "newPlaylistFromFile(QString)\0path\0"
    "newPlaylistFromPath(QString)\0"
    "addToPlaylistFromIndex(QModelIndex)\0"
    "addToPlaylistFromThread()\0"
    "addToPlaylistFromFile(QString)\0"
    "addToPlaylistFromPath(QString)\0"
    "playlistFromThread()\0query\0"
    "matchTracks(QString)\0item\0"
    "toggleTableStarItem(QTableWidgetItem*)\0"
    ",,,\0updateStats(int,int,int,QString)\0"
    "newState\0setPlayingModeState(int)\0"
    "writeFavouritesToFile()\0"
};

const QMetaObject okPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_okPlayer,
      qt_meta_data_okPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &okPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *okPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *okPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_okPlayer))
        return static_cast<void*>(const_cast< okPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int okPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statusChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: stop(); break;
        case 3: pause(); break;
        case 4: play(); break;
        case 5: play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: play((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: playRandom(); break;
        case 8: playCurrent(); break;
        case 9: prev(); break;
        case 10: next(); break;
        case 11: nextAuto(); break;
        case 12: newPlaylistFromIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 13: newPlaylistFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: newPlaylistFromPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: addToPlaylistFromIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 16: addToPlaylistFromThread(); break;
        case 17: addToPlaylistFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: addToPlaylistFromPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: playlistFromThread(); break;
        case 20: matchTracks((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: toggleTableStarItem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 22: updateStats((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 23: setPlayingModeState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: writeFavouritesToFile(); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void okPlayer::statusChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
