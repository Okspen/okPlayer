#include "playlistviewfrontend.h"

PlaylistViewFrontend::PlaylistViewFrontend(PlaylistView *view, QObject *parent) :
    m_view(view), QObject(parent)
{
    m_current = -1;

    m_delegate = new TrackDelegate;
    m_view->setItemDelegate(m_delegate);

    m_model = new PlaylistModel(this);

    m_sortModel = new QSortFilterProxyModel(this);
    m_sortModel->setSourceModel(m_model);
    m_sortModel->setFilterRole(PlaylistModel::SearchRole);
    m_sortModel->setDynamicSortFilter(true);
    m_sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    m_view->setModel(m_sortModel);

    connect(m_model, SIGNAL(trackSelected(Playlist *,int)), this, SIGNAL(trackSelected(Playlist *, int)));
}

PlaylistViewFrontend::~PlaylistViewFrontend()
{
    delete m_sortModel;
    delete m_model;
    delete m_delegate;
}

void PlaylistViewFrontend::setPlayer(Player *player)
{
    if (player == m_player)
        return;

    if (m_player) {
        disconnect();
    }

    m_player = player;
    connect(player->playlistManager, SIGNAL(currentPlaylistChanged(Playlist*)), this, SLOT(setPlaylist(Playlist*)));
    connect(player->trackCycler, SIGNAL(trackChanged(int)), this, SLOT());
}

void PlaylistViewFrontend::setFavorites(Playlist *favorites)
{
    m_model->setFavorites(favorites);
}

void PlaylistViewFrontend::setTrack(int num)
{
    if (num <0 || num >= m_model->rowCount(QModelIndex()))
        return;

    m_current = num;
    m_model->setCurrent(num);

    QModelIndex currentIndex = index(num);
    m_view->setCurrentIndex(currentIndex);
    m_view->scrollTo(currentIndex, QAbstractItemView::EnsureVisible);
}

void PlaylistViewFrontend::setTrack(Playlist *playlist, int index)
{
    if (m_model->playlist() != playlist)
        return;
    setTrack(index);
}

void PlaylistViewFrontend::setPlaylist(Playlist *playlist)
{
    m_model->setPlaylist(playlist);
    m_view->scrollToTop();
}

void PlaylistViewFrontend::updatePlaylist()
{
    m_model->update();
}

void PlaylistViewFrontend::setFilter(const QString &pattern)
{
    m_sortModel->setFilterFixedString(pattern);
    m_view->scrollTo(index(m_current), QAbstractItemView::PositionAtCenter);

    if (pattern.isEmpty())
        m_view->setEmptyPlaylistMessage("Empty playlist");
    else
        m_view->setEmptyPlaylistMessage("No results for: "+pattern);
}

QModelIndex PlaylistViewFrontend::index(int row)
{
    return m_sortModel->mapFromSource(m_model->index(row));
}


Playlist *PlaylistViewFrontend::favorites() const
{
    return m_model->favorites();
}
