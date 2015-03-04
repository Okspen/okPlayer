#include "trackcycler.h"
#include "player/player.h"

TrackCycler::TrackCycler(QObject *parent) :
    QObject(parent),
    m_playlist(0)
{
}

Playlist *TrackCycler::playlist() const
{
    return m_playlist;
}

PlayId TrackCycler::current() const
{
    return PlayId(m_playlist, m_order.currentIndex());
}

int TrackCycler::currentIndex() const
{
    return m_order.currentIndex();
}

bool TrackCycler::shuffle() const
{
    return m_order.shuffle();
}

void TrackCycler::prev()
{
    m_order.prev();
    setTrack(m_order.currentIndex());
}

void TrackCycler::next()
{
    m_order.next();
    setTrack(m_order.currentIndex());
}

void TrackCycler::rand()
{
    m_order.rand();
    setTrack(m_order.currentIndex());
}

void TrackCycler::setShuffle(bool shuffle)
{
    if (m_order.shuffle() == shuffle)
        return;

    m_order.setShuffle(shuffle);

    emit shuffleChanged(shuffle);
}

void TrackCycler::setPlaylist(Playlist *playlist)
{
    if (playlist == m_playlist)
        return;

    m_order.setPlaylist(playlist);
    m_playlist = playlist;

    emit playlistChanged(playlist);
}

void TrackCycler::setTrack(int i, bool notify)
{
    if (m_playlist == 0 || m_playlist->isEmpty() || i < 0 || i >= m_playlist->count())
        return;

    m_order.setCurrentIndex(i);

    if (notify) {
        emit trackChanged(m_playlist->at(i));
        emit trackChanged(PlayId(m_playlist, i));
    }
}

void TrackCycler::shuffleTracks()
{
    m_order.shuffleTracks();
}

void TrackCycler::play(PlayId id)
{
    setPlaylist(id.playlist());
    setTrack(id.index());
}
