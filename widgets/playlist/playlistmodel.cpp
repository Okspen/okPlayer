#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) :
    QAbstractListModel(parent),
    m_playlist(0),
    m_cycler(0),
    m_media(0),
    m_favorites(0)
{
}

Playlist *PlaylistModel::playlist() const
{
    return m_playlist;
}

void PlaylistModel::setTrackCycler(TrackCycler *cycler)
{
    if (m_cycler) {
        disconnect(m_cycler, SIGNAL(trackChanged(PlayId)),          this, SLOT(onTrackChanged(PlayId)));
        disconnect(m_cycler, SIGNAL(playlistChanged(Playlist*)),    this, SLOT(setPlaylist(Playlist*)));
    }

    if (cycler != 0) {
        m_cycler = cycler;
        connect(m_cycler, SIGNAL(trackChanged(PlayId)),         this, SLOT(onTrackChanged(PlayId)));
        connect(m_cycler, SIGNAL(playlistChanged(Playlist*)),   this, SLOT(setPlaylist(Playlist*)));
    }
}

void PlaylistModel::setMediaLibrary(MediaLibrary *media)
{
    if (m_media)
        disconnect(m_media, SIGNAL(dataChanged(QUrl)), this, SLOT(onMediaChanged(QUrl)));

    if (media != 0) {
        m_media = media;
        connect(m_media, SIGNAL(dataChanged(QUrl)), this, SLOT(onMediaChanged(QUrl)));
    }
}

void PlaylistModel::setFavoritesManager(FavoritesManager *favorites)
{
    if (m_favorites) {
        disconnect(m_favorites, SIGNAL(added(QUrl)),    this,   SLOT(onMediaChanged(QUrl)));
        disconnect(m_favorites, SIGNAL(removed(QUrl)),  this,   SLOT(onMediaChanged(QUrl)));
    }

    if (favorites != 0) {
        m_favorites = favorites;
        connect(m_favorites,   SIGNAL(added(QUrl)),    this,   SLOT(onMediaChanged(QUrl)));
        connect(m_favorites,   SIGNAL(removed(QUrl)),  this,   SLOT(onMediaChanged(QUrl)));
    }
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (m_playlist == 0)
        return 0;

    return m_playlist->count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (m_playlist == 0)
        return QVariant();

    if (index.isValid() == false)
        return QVariant();

    int row = index.row();
    QUrl url = m_playlist->at(row);

    QString title;
    QString artist;
    QString album;
    QString searchString;
    QString duration;

    if (m_media != 0) {
        MediaInfo *mediaInfo = m_media->info(url);
        title       = mediaInfo->title();
        artist      = mediaInfo->artist();
        album       = mediaInfo->album();
        searchString = mediaInfo->searchString();

        int durationSeconds = mediaInfo->duration();
        if (durationSeconds > 0) {
            QString format = "m:ss";
            if (durationSeconds > 60*60)
                format = "H:mm:ss";
            duration = QTime(0,0,0,0).addSecs(mediaInfo->duration()).toString(format);
        }
    }

    if (role == Qt::DisplayRole) {
        int displayRow = row + 1;
        if (m_media == 0 || (artist.isEmpty() && title.isEmpty()))
            return QString("%1. %2").arg(displayRow).arg(url.fileName());

        if (title.isEmpty())
            title = "Unknown Title";
        if (artist.isEmpty())
            artist = "Unknown Artist";
        if (album.isEmpty())
            album = "Unknown Album";

        return QString("%1. %2 – %3").arg(displayRow).arg(artist).arg(title);
    }

    if (role == TitleRole)
        return title;

    if (role == ArtistRole)
        return artist;

    if (role == AlbumRole)
        return album;

    if (role == UrlRole)
        return url;

    if (role == Qt::ToolTipRole) {
        if (url.isLocalFile())
            return "Location: "+url.toLocalFile();
        return "Location: "+url.toString();
    }

    if (role == FavoriteRole) {
        if (!m_favorites) return false;
        return m_favorites ? m_favorites->isFavorite(url) : false;
    }

    if (role == LocalRole)
        return url.isLocalFile();

    if (role == CurrentRole) {
        return (row == m_cycler->currentIndex());
    }

    if (role == TimeRole) {
        PlayId current = m_cycler->current();
        if (PlayId(m_playlist, row) == current)
            return m_currentTime;
    }

    if (role == DurationRole) {
        return duration;
    }

    if (role == SearchRole)
        return searchString;

    return QVariant();
}

bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QAbstractListModel::setData(index, value, role);

    if (index.isValid() == false)
        return false;

    int row = index.row();

    if (role == FavoriteRole) {
        bool isFavorite = value.toBool();
        QUrl url = m_playlist->at(row);

        isFavorite ? m_favorites->add(url) : m_favorites->remove(url);

        return true;
    }

    if (role == CurrentRole && value.toBool()) {
        m_cycler->play(PlayId(m_playlist, row));
        return true;
    }

    return false;
}

bool PlaylistModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (m_playlist->count() <= 0 || row < 0 || row >= rowCount(parent))
        return false;

    emit beginRemoveRows(parent, row, row + count - 1);

    m_playlist->removeAt(row, count);

    emit endRemoveRows();
    return true;
}

void PlaylistModel::setPlaylist(Playlist *playlist)
{
    emit beginResetModel();

    m_playlist = playlist;

    if (m_playlist) {
        disconnect(m_playlist, SIGNAL(removed(int,int)),this, SLOT(updatePlaylist()));
        disconnect(m_playlist, SIGNAL(countChanged()),  this, SLOT(updatePlaylist()));
        disconnect(m_playlist, SIGNAL(destroyed()),     this, SLOT(onPlaylistDestroyed()));
    }

    if (m_playlist == 0)
        return;

    connect(m_playlist, SIGNAL(removed(int,int)),   this, SLOT(updatePlaylist()));
    connect(m_playlist, SIGNAL(countChanged()),     this, SLOT(updatePlaylist()));
    connect(m_playlist, SIGNAL(destroyed()),        this, SLOT(onPlaylistDestroyed()));

    if (m_media)
        m_media->findInfo(m_playlist);

    emit endResetModel();
}

void PlaylistModel::updatePlaylist()
{
    emit beginResetModel();
    emit endResetModel();
}

void PlaylistModel::onTrackChanged(PlayId id)
{
    emit dataChanged(createIndex(id.index(), 0),        createIndex(id.index(), 0),         QVector<int>() << CurrentRole);
}

void PlaylistModel::onMediaChanged(const QUrl &url)
{
    if (m_playlist == 0)
        return;

    int urlCount = m_playlist->count(url);

    if (urlCount < 1)
        return;

    int index = -1;
    int lastIndex = 0;
    for (int i=0; i<urlCount; i++) {
        index = m_playlist->indexOf(url, lastIndex);
        emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int>() << Qt::DisplayRole);
        lastIndex = index;
    }
}

void PlaylistModel::onPlaylistDestroyed()
{
    emit beginResetModel();
    m_playlist = 0;
    emit endResetModel();
}
