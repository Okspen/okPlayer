#include "playlisthistory.h"
#include "player/player.h"

PlaylistHistory::PlaylistHistory(QObject *parent) : QObject(parent)
{
    m_playlists     = new QList<Playlist*>;
    m_currentIndex  = -1;
    m_playlistId    = 1;
}

PlaylistHistory::~PlaylistHistory()
{
    for (int i=0; i < m_playlists->count(); ++i)
        delete m_playlists->at(i);

    delete m_playlists;
}

void PlaylistHistory::prev()
{
    if (m_playlists->count() < 2)
        return;

    --m_currentIndex;
    if (!inRange(m_currentIndex))
        m_currentIndex = m_playlists->count()-1;

    emit currentChanged(m_playlists->at(m_currentIndex));
}

void PlaylistHistory::next()
{
    if (m_playlists->count() < 2)
        return;

    ++m_currentIndex;
    if (!inRange(m_currentIndex))
        m_currentIndex = 0;

    emit currentChanged(m_playlists->at(m_currentIndex));
}

void PlaylistHistory::addToCurrent(const QList<QUrl> &filelist)
{
    Playlist *playlist = current();
    if (playlist != 0)
        playlist->append(filelist);
    else
        replaceCurrent(new Playlist(filelist));
}

void PlaylistHistory::switchPlaylist(int index)
{
    if (!inRange(index) || m_currentIndex == index)
        return;

    m_currentIndex = index;
//    if (index == 0) {
//        m_current = m_playlists->begin();
//    } else if (index == m_playlists->count()) {
//        m_current = m_playlists->end();
//    } else {
//        m_current = m_playlists->begin();
//        for (int i=0; i<index; i++)
//            ++m_current;
//    }

    emit currentChanged(m_playlists->at(m_currentIndex));
}

void PlaylistHistory::deleteCurrentPlaylist()
{
    if (!inRange(m_currentIndex))
        return;

    int count = m_playlists->count();

    if (count == 1) {
        //emit currentChanged(0);
        delete m_playlists->takeAt(m_currentIndex);
        m_currentIndex = -1;
        emit countChanged();
        return;
    }
    // current playlist is the last one in list
    if (m_currentIndex == count - 1) {
        delete m_playlists->takeAt(m_currentIndex);
        m_currentIndex--;
        emit currentChanged(m_playlists->at(m_currentIndex));
        emit countChanged();
        return;
    }
    // current playlist is in the middle
    if ((m_currentIndex >= 0) && (m_currentIndex < (count - 1))) {
        delete m_playlists->takeAt(m_currentIndex);
        emit currentChanged(m_playlists->at(m_currentIndex));
        emit countChanged();
        return;
    }
}

bool PlaylistHistory::inRange(int index) const
{
    return (!m_playlists->isEmpty() && index >= 0 && index < m_playlists->count());
}

void PlaylistHistory::replaceCurrent(Playlist *playlist)
{
    if (playlist->isEmpty()) {
        delete playlist;
        return;
    }

    if (inRange(m_currentIndex) && m_playlists->at(m_currentIndex)->isEmpty()) {
        m_playlists->at(m_currentIndex)->append(playlist->urls());
        m_playlists->at(m_currentIndex)->setName(QString("Playlist %1").arg(m_playlistId++));
        delete playlist;
    } else {
        m_playlists->append(playlist);
        playlist->setName(QString("Playlist %1").arg(m_playlistId++));
        m_currentIndex = m_playlists->count()-1;
    }

    emit currentChanged(m_playlists->at(m_currentIndex));
    emit countChanged();
}

//void PlaylistHistory::appendCurrent(Playlist playlist)
//{
//    if (playlist.isEmpty() || !inRange(m_currentIndex))
//        return;

//    m_playlists->at(m_currentIndex)->append(playlist.urls());
//    emit updated(m_playlists->at(m_currentIndex));
//}

QList<Playlist*>* PlaylistHistory::playlists() const
{
    return m_playlists;
}

Playlist *PlaylistHistory::current() const
{
    if (inRange(m_currentIndex))
        return m_playlists->at(m_currentIndex);
    return 0;
}

int PlaylistHistory::currentIndex() const
{
    return m_currentIndex;
}
