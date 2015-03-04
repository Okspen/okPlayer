#ifndef TRACKCYCLER_H
#define TRACKCYCLER_H

#include <QObject>
#include "playid.h"
#include "playorder.h"
#include "player/playersettings.h"
#include <QDebug>

class TrackCycler : public QObject
{
    Q_OBJECT
public:
    explicit TrackCycler(QObject *parent = 0);
    Playlist *playlist() const;
    PlayId  current() const;
    int     currentIndex() const;
    bool    shuffle() const;
    
signals:
    void shuffleChanged(bool);
    void trackChanged(QUrl);
    void trackChanged(PlayId);
    void playlistChanged(Playlist *playlist);
    
public slots:
    void play(PlayId id);
    void prev();
    void next();
    void rand();
    void setShuffle(bool shuffle);
    void setPlaylist(Playlist *playlist);
    void shuffleTracks();

private:
    Playlist    *m_playlist;
    PlayOrder   m_order;

    /* Saves the track number, playlist and notifies if checked */
    void setTrack(int i, bool notify = true);
};

#endif // TRACKCYCLER_H
