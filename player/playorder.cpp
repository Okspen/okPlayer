#include "playorder.h"

PlayOrder::PlayOrder(QObject *parent) : QObject(parent)
{
    m_index     = -1;
    m_shuffle   = false;
    m_playlist  = 0;
}

PlayOrder::~PlayOrder()
{
}

int PlayOrder::currentIndex() const
{
    if (m_index < 0 || m_index >= m_order.count())
        return -1;
    return m_order.at(m_index);
}

void PlayOrder::setCurrentIndex(int index)
{
    if (index < 0 || index >= m_order.count() || m_index == index)
        return;
    m_index = m_order.indexOf(index);
}

bool PlayOrder::shuffle() const
{
    return m_shuffle;
}

void PlayOrder::setShuffle(bool shuffle)
{
    m_shuffle = shuffle;
    if (m_shuffle)
        shuffleTracks();
    else
        resetOrder();
}

Playlist *PlayOrder::playlist() const
{
    return m_playlist;
}

void PlayOrder::setPlaylist(Playlist *playlist)
{
    if (m_playlist) {
        if (m_index != -1)
            m_lastTracks.insert(m_playlist, currentIndex());

        disconnect(m_playlist, SIGNAL(countChanged()),  this, SLOT(onCountChanged()));
        disconnect(m_playlist, SIGNAL(removed(int,int)),this, SLOT(onRemoved(int,int)));
        disconnect(m_playlist, SIGNAL(destroyed()),     this, SLOT(onDestroyed()));
    }

    m_playlist = playlist;
    if (m_playlist) {
        connect(m_playlist, SIGNAL(countChanged()),     this, SLOT(onCountChanged()));
        connect(m_playlist, SIGNAL(removed(int,int)),   this, SLOT(onRemoved(int,int)));
        connect(m_playlist, SIGNAL(destroyed()),        this, SLOT(onDestroyed()));
    }

    syncOrder();
    if (m_shuffle)
        shuffleTracks();

    m_index = -1;
}

void PlayOrder::shuffleTracks()
{
    if (m_order.isEmpty())
        return;

    shuffleOrder();

    if (m_order.count() >= 2) {
        while (m_order.at(0) == m_index)
            shuffleOrder();
    }
}

void PlayOrder::prev()
{
    if (m_order.isEmpty())
        return;

    --m_index;
    if (m_index < 0) {
        m_index = m_order.count()-1;

        if (m_shuffle)
            shuffleOrder();
    }
}

void PlayOrder::next()
{
    if (m_order.isEmpty())
        return;

    if (m_index == -1) {
        m_index = m_order.indexOf(m_lastTracks.value(m_playlist, 0));
        next();
        return;
    }

    int count = m_playlist->playCount(currentIndex());
    --count;
    if (count == 0) {
        m_playlist->setPlayCount(currentIndex(), 1);

        ++m_index;
        if (m_index >= m_order.count()) {
            m_index = 0;

            if (m_shuffle)
                shuffleOrder();
        }
    } else {
        m_playlist->setPlayCount(currentIndex(), count);
    }
}

void PlayOrder::rand()
{
    if (m_order.isEmpty())
        return;

    if (m_order.count() > 1) {
        int track = 0;
        while (m_index == track)
            track = qrand() % m_order.count();
        m_index = track;
    }
}

void PlayOrder::shuffleOrder()
{
    if (m_order.isEmpty())
        return;

    int index = currentIndex();

    for (int i = m_order.count() - 1; i >= 1; --i)
        m_order.swap(qrand() % i, i);

    m_index = m_order.indexOf(index);
}

void PlayOrder::resetOrder()
{
    int index = currentIndex();

    for (int i=0; i<m_order.count(); ++i)
        m_order.replace(i, i);

    m_index = m_order.indexOf(index);
}

void PlayOrder::syncOrder()
{
    int current = currentIndex();

    m_order.clear();

    if (m_playlist == 0)
        return;

    for (int i=0; i<m_playlist->count(); ++i)
        m_order.append(i);

    m_index = m_order.indexOf(current);
}

void PlayOrder::onCountChanged()
{
    syncOrder();

    if (m_shuffle)
        shuffleTracks();
}

void PlayOrder::onDestroyed()
{
    m_lastTracks.remove(m_playlist);
    m_playlist  = 0;
    m_index     = -1;

    syncOrder();
}

void PlayOrder::onRemoved(int i, int count)
{
    int current = currentIndex();
    int first   = i;
    int last    = first + count - 1;

    syncOrder();
    if (m_shuffle)
        shuffleTracks();

    if (current >= first && current <= last) {
        m_index = -1;
    } else if (current > last) {
        m_index = m_order.indexOf(current - count);
    } else {
        m_index = m_order.indexOf(current);
    }
}
