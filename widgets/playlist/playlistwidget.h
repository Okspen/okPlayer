#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include "trackdelegate.h"
#include "playlistmodel.h"
#include "favoritesfiltermodel.h"

namespace Ui {
class PlaylistWidget;
}

class PlaylistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistWidget(QWidget *parent = 0);
    ~PlaylistWidget();

public slots:
    void setPlaylist(Playlist *playlist);
    void setFilter(const QString &pattern);
    void setFavoritesFilterEnabled(bool enabled);

private:
    Ui::PlaylistWidget *ui;

    TrackCycler             *m_cycler;

    TrackDelegate           *m_delegate;
    PlaylistModel           *m_model;
    QSortFilterProxyModel   *m_sortModel;
    FavoritesFilterModel    *m_favFilterModel;

    /* Return row's index in sort model */
    QModelIndex sortIndex(int row) const;
    QString chooseEmptyMessage() const;

private slots:
    void onTrackChanged(PlayId prevId, PlayId curId);
    void onPlaylistCountChanged();
    void onPlaylistDestroyed();

    void scrollToCurrent();
};

#endif // PLAYLISTWIDGET_H
