#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QListView>
#include <QContextMenuEvent>
#include <QMenu>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QMimeData>
#include <QVariant>

#include "playlistmodel.h"
#include "trackdelegate.h"
#include "mediadroppeddialog.h"
#include "player/player.h"
#include "player/playersettings.h"
#include "widgets/playlist/playcountdialog.h"

class PlaylistView : public QListView
{
    Q_OBJECT
public:
    explicit PlaylistView(QWidget *parent = 0);
    void setEmptyMessage(const QString &emptyMessage);

public slots:
    void toggleFavorites(bool enabled);
    void setFavoritesEnabled(bool enabled);

signals:
    void showFavoritesToggled(bool);
    
protected:
    void paintEvent(QPaintEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent* event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

private:
    QString     m_emptyMessage;
    QAction     *m_showFavoritesAction;
};

#endif // PLAYLISTVIEW_H
