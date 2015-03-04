#include "playid.h"

PlayId::PlayId()
    : m_playlist(0), m_index(-1)
{
}

PlayId::PlayId(Playlist *playlist, int index)
    : m_playlist(playlist), m_index(index)
{
}

Playlist *PlayId::playlist() const
{
    return m_playlist;
}

int PlayId::index() const
{
    return m_index;
}

void PlayId::setIndex(int index)
{
    if (index < 0 || index >= m_playlist->count())
        m_index = -1;
    m_index = index;
}

QUrl PlayId::url() const
{
    return m_playlist->at(m_index);
}

bool PlayId::isValid() const
{
    return (m_playlist != 0
            && m_index >=0
            && m_index < m_playlist->count());
}

bool PlayId::operator==(const PlayId& id) {
    return isValid() && (m_index == id.index()) && (m_playlist == id.playlist());
}

PlayId PlayId::operator++()
{
    if (m_playlist == 0 || m_playlist->isEmpty()) {
        m_index = -1;
        return PlayId(m_playlist, -1);
    }

    ++m_index;
    if (!inRange())
        m_index = 0;
    return PlayId(m_playlist, m_index);
}

PlayId PlayId::operator--()
{
    if (m_playlist == 0 || m_playlist->isEmpty()) {
        m_index = -1;
        return PlayId(m_playlist, -1);
    }

    --m_index;
    if (!inRange())
        m_index = m_playlist->count() - 1;
    return PlayId(m_playlist, m_index);
}

bool PlayId::inRange()
{
    if (m_playlist == 0 || m_playlist->isEmpty())
        return false;

    return (m_index >= 0) && (m_index < m_playlist->count());
}
