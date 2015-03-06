#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractListModel>
#include "player/player.h"

class HistoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HistoryModel(QObject *parent = 0);
    void setHistory(PlaylistHistory *history);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant dataNoPlaylists(const QModelIndex &index, int role) const;

public slots:
    void changePlaylist(Playlist *playlist);

private:
    PlaylistHistory     *m_history;
    QList<Playlist*>    *m_playlists;
    QString playlistToString(Playlist *playlist) const;

private slots:
    void onPlaylistCountChanged();
    void onTrackCountChanged();
};

#endif // HISTORYMODEL_H
