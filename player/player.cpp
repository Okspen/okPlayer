#include "player.h"

Player* Player::m_instance = 0;

Player *Player::instance(QObject *parent)
{
    if (m_instance == 0)
        m_instance = new Player(parent);

    return m_instance;
}

void Player::deleteInstance()
{
    if (m_instance)
        delete m_instance;
}

Player::Player(QObject *parent) :
    QObject(parent)
{
    m_audio         = new BASS::Core;
    m_audio->init();
//    QThread *thread = new QThread;
//    m_audio->moveToThread(thread);

//    connect(thread, SIGNAL(started()),  m_audio,    SLOT(init()));
//    connect(thread, SIGNAL(finished()), thread,     SLOT(deleteLater()));
//    connect(thread, SIGNAL(finished()), m_audio,    SLOT(deleteLater()));
//    thread->start();

    m_cycler    = new TrackCycler(this);
    m_history   = new PlaylistHistory(this);
    m_folder    = new FolderPlayer(this);
    m_favorites = new FavoritesManager(this);
    //m_media = 0;
    m_media     = new MediaLibrary(this);

    connect(m_cycler,   SIGNAL(trackChanged(QUrl)), m_audio,    SLOT(play(QUrl)));
    connect(m_audio,    SIGNAL(finished()),         m_cycler,   SLOT(next()));
    connect(m_history,  SIGNAL(currentChanged(Playlist*)), m_cycler,SLOT(setPlaylist(Playlist*)));
}

BASS::Core *Player::audio() const
{
    return m_audio;
}

TrackCycler *Player::cycler() const
{
    return m_cycler;
}

PlaylistHistory *Player::history() const
{
    return m_history;
}

FolderPlayer *Player::folder() const
{
    return m_folder;
}

FavoritesManager *Player::favorites() const
{
    return m_favorites;
}

MediaLibrary *Player::media() const
{
    return m_media;
}
