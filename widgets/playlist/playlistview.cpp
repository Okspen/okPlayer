#include "playlistview.h"

PlaylistView::PlaylistView(QWidget *parent) :
    QListView(parent)
{
    setAcceptDrops(true);
    setUniformItemSizes(true);

    m_emptyMessage          = "Empty playlist";

    m_showFavoritesAction   = new QAction("Show Only Favorites", this);
    m_showFavoritesAction->setCheckable(true);
    connect(m_showFavoritesAction, SIGNAL(toggled(bool)), this, SIGNAL(showFavoritesToggled(bool)));
}

void PlaylistView::setEmptyMessage(const QString &emptyMessage)
{
    m_emptyMessage = emptyMessage;
}

void PlaylistView::toggleFavorites(bool enabled)
{
    m_showFavoritesAction->setChecked(enabled);
}

void PlaylistView::setFavoritesEnabled(bool enabled)
{
    m_showFavoritesAction->setEnabled(enabled);
}

void PlaylistView::mouseReleaseEvent(QMouseEvent *event)
{
    QListView::mouseReleaseEvent(event);
    
    Qt::MouseButton button = event->button();
    if (button == Qt::XButton1)
        Player::instance()->history()->prev();
    if (button == Qt::XButton2)
        Player::instance()->history()->next();
}

void PlaylistView::dragEnterEvent(QDragEnterEvent *event)
{
    QListView::dragEnterEvent(event);
    event->accept();
}

void PlaylistView::dragMoveEvent(QDragMoveEvent *event)
{
    QListView::dragMoveEvent(event);
    event->accept();
}

void PlaylistView::dropEvent(QDropEvent *event)
{
    QListView::dropEvent(event);

    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        MediaDroppedDialog dialog(this);
        if (!dialog.exec())
            return;

        bool append     = dialog.toAppend();
        bool recursive  = !dialog.root();
        
        QList<QUrl> urls = mimeData->urls();
        QStringList pathList;
        for (int i=0; i<urls.count(); i++)
            pathList.append(urls.at(i).toLocalFile());

        Player::instance()->folder()->play(pathList, recursive, append);
    }
    
    event->acceptProposedAction();
}

void PlaylistView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    bool indexIsValid = index.isValid();

    QUrl url = index.data(PlaylistModel::UrlRole).toUrl();

    QAction playAction("Play", this);
    playAction.setEnabled(indexIsValid);

    QAction playSeveralTimes("Play Several Times", this);
    playSeveralTimes.setEnabled(indexIsValid);

    bool isFavorite = index.data(PlaylistModel::FavoriteRole).toBool();
    QString favoritesText = (isFavorite) ? "Remove from Favorites" : "Add to Favorites";
    QAction favoritesAction(favoritesText, this);
    favoritesAction.setEnabled(indexIsValid);

    QAction openFolder("Open Containing Folder", this);
    QFileInfo fileInfo(url.toLocalFile());
    openFolder.setEnabled(index.isValid() && fileInfo.exists());

    QAction removeAction("Remove", this);
    removeAction.setEnabled(indexIsValid);

    QMenu menu;
    menu.addAction(&playAction);
    menu.addAction(&playSeveralTimes);
    menu.addAction(&favoritesAction);
    menu.addAction(&openFolder);
    menu.addAction(&removeAction);
    menu.addSeparator();
    menu.addAction(m_showFavoritesAction);

    QAction* resultAction = menu.exec(event->globalPos());
    if (resultAction == &playAction) {
        model()->setData(index, true, PlaylistModel::CurrentRole);
        return;
    }

    if (resultAction == &playSeveralTimes) {
        PlayCountDialog d(this);
        d.setPlayCount(index.data(PlaylistModel::PlayCountRole).toInt());

        int result = d.exec();
        if (result > 0)
            model()->setData(index, d.playCount(), PlaylistModel::PlayCountRole);
        return;
    }

    if (resultAction == &favoritesAction) {
        model()->setData(index, !isFavorite, PlaylistModel::FavoriteRole);
        return;
    }

    if (resultAction == &openFolder) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteDir().absolutePath()));
        return;
    }

    if (resultAction == &removeAction) {
        model()->removeRows(index.row(), 1);
        return;
    }
}

void PlaylistView::paintEvent(QPaintEvent *event)
{
    QListView::paintEvent(event);

    if (model()->rowCount() == 0) {
        QPalette palette;
        QPainter painter(viewport());
        painter.setPen(palette.color(QPalette::Inactive, QPalette::Text));
        painter.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap, m_emptyMessage);
    }
}
