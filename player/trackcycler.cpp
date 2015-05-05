#include "trackcycler.h"
#include "player/player.h"

TrackCycler::TrackCycler(QObject *parent) :
    QObject(parent)
{
}

Playlist *TrackCycler::playlist() const
{
    return m_order.playlist();
}

PlayId TrackCycler::current() const
{
    return PlayId(m_order.playlist(), m_order.currentIndex());
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
    if (playlist == m_order.playlist())
        return;

    m_order.setPlaylist(playlist);
//    if (playlist == m_current.playlist())
//        m_order.setCurrentIndex(m_current.index());

    emit playlistChanged(playlist);
}

void TrackCycler::setTrack(int i, bool notify)
{
    Playlist *p = m_order.playlist();

    if (p == 0 || p->isEmpty() || i < 0 || i >= p->count())
        return;

    PlayId prev = m_order.currentId();
    m_order.setCurrentIndex(i);
    PlayId current = m_order.currentId();

    if (notify) {
        emit trackChanged(p->at(i));
        emit trackChanged(prev, current);
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
