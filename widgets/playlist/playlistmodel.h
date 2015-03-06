#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QAction>
#include "../../player/player.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TrackRoles {
        TitleRole       = Qt::UserRole + 1,
        ArtistRole      = Qt::UserRole + 2,
        AlbumRole       = Qt::UserRole + 3,
        FavoriteRole    = Qt::UserRole + 4,
        UrlRole         = Qt::UserRole + 5,
        LocalRole       = Qt::UserRole + 6,
        CurrentRole     = Qt::UserRole + 7,
        TimeRole        = Qt::UserRole + 8,
        DurationRole    = Qt::UserRole + 9,
        PlayCountRole   = Qt::UserRole + 10,
        SearchRole      = Qt::UserRole + 11
    };

    explicit PlaylistModel(QObject *parent = 0);
    Playlist *playlist() const;

    void setTrackCycler(TrackCycler *cycler);
    void setMediaLibrary(MediaLibrary *media);
    void setFavoritesManager(FavoritesManager *favorites);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

public slots:
    void setPlaylist(Playlist *playlist);
    void updatePlaylist();

protected:
    QString     m_currentTime;
    Playlist    *m_playlist;

    TrackCycler         *m_cycler;
    MediaLibrary        *m_media;
    FavoritesManager    *m_favorites;

private:
    void setCurrent(int current);
    QVariant dataNoMedia(const QModelIndex &index, int role) const;

private slots:
    void onTrackChanged(PlayId id);
    void onMediaChanged(const QUrl &url);
    void onPlaylistDestroyed();
};

#endif // PLAYLISTMODEL_H
