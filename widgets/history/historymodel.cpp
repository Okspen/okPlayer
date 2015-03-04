#include "historymodel.h"

HistoryModel::HistoryModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_history = Player::instance()->history();
    connect(m_history, SIGNAL(currentChanged(Playlist*)), this, SLOT(changePlaylist(Playlist*)));

    m_playlists = m_history->playlists();
    if (m_playlists->count()) {
        for (int i = 0; i < m_playlists->count(); i++)
            connect(m_playlists->at(i), SIGNAL(countChanged()), this, SLOT(onTrackCountChanged()), Qt::UniqueConnection);
    }

    connect(m_history, SIGNAL(countChanged()), this, SLOT(onPlaylistCountChanged()));
}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (m_playlists == 0 || m_playlists->count() == 0)
        return 1;

    return m_playlists->count();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    if (m_playlists == 0 || m_playlists->count() == 0)
        return dataNoPlaylists(index, role);

    if (index.isValid() == false)
        return QVariant();

    int row = index.row();

    if (role == Qt::DisplayRole)
        return playlistToString(m_playlists->at(row));

    if (role == Qt::SizeHintRole)
        return QSize(0, 18);

    return QVariant();
}

QVariant HistoryModel::dataNoPlaylists(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return "No playlists";

    if (role == Qt::SizeHintRole)
        return QSize(0, 18);

    return QVariant();
}

void HistoryModel::changePlaylist(Playlist *playlist)
{
    if (playlist == 0)
        return;

    emit beginResetModel();
    connect(playlist, SIGNAL(countChanged()), this, SLOT(onPlaylistCountChanged()), Qt::UniqueConnection);
    emit endResetModel();
}

QString HistoryModel::playlistToString(Playlist *playlist) const
{
    if (playlist == 0)
        return QString("No Playlists");

    QString name = playlist->name();
    int count = playlist->count();

    if (name.isEmpty()) {
        int index = m_playlists->indexOf(playlist);
        if (index == -1)
            return QString("Playlist (%1 tracks)").arg(count);
        return QString("Playlist %1 (%2 tracks)").arg(index + 1).arg(count);
    }
    return QString("%1 (%2 tracks)").arg(name).arg(count);
}

void HistoryModel::onPlaylistCountChanged()
{
    emit beginResetModel();
    emit endResetModel();
}

void HistoryModel::onTrackCountChanged()
{
    Playlist *playlist = (Playlist*) QObject::sender();
    if (!playlist)
        return;

    int row = m_playlists->indexOf(playlist);
    emit dataChanged(createIndex(row,0), createIndex(row,0), QVector<int>() << Qt::DisplayRole);
}
