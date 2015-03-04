#ifndef PLAYLISTVIEWFRONTEND_H
#define PLAYLISTVIEWFRONTEND_H

#include <QObject>
#include "widgets/playlist/playlistview.h"
#include "player/player.h"

class PlaylistViewFrontend : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistViewFrontend(PlaylistView *view, QObject *parent = 0);
    ~PlaylistViewFrontend();

    void setPlayer(Player *player);
    void setFavorites(Playlist *favorites);
    Playlist* favorites() const;
    
signals:
    void trackSelected(Playlist *, int);
    
public slots:
    void setTrack(int num);
    void setTrack(Playlist *playlist, int index);
    void setPlaylist(Playlist *playlist);
    void updatePlaylist();
    void setFilter(const QString& pattern);

private:
    Player                  *m_player;
    PlaylistView            *m_view;
    TrackDelegate           *m_delegate;
    PlaylistModel           *m_model;
    QSortFilterProxyModel   *m_sortModel;
    int                     m_current;
    /* Return row's index in sort model */
    QModelIndex index(int row);
    
};

#endif // PLAYLISTVIEWFRONTEND_H
