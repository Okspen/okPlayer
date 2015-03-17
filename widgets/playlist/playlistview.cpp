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

void PlaylistView::keyReleaseEvent(QKeyEvent *event)
{
    QListView::keyReleaseEvent(event);

    QModelIndexList selected = selectedIndexes();
    int selectedCount = selected.count();

    QAbstractItemModel *m = model();
    if (m == 0)
        return;

    switch (event->key()) {

    case Qt::Key_Enter:
    case Qt::Key_Return:
        if (selectedCount == 1)
            m->setData(selected.at(0), true, PlaylistModel::CurrentRole);
        break;

    case Qt::Key_Delete:
        for (int i = selectedCount-1; i >= 0; --i)
            m->removeRows(selected.at(i).row(), 1);
        break;

    case Qt::Key_S:
        bool allFavorite = true;
        for (int i = 0; i < selectedCount && allFavorite; ++i) {
            allFavorite = selected.at(i).data(PlaylistModel::FavoriteRole).toBool();
        }

        for (int i = 0; i < selectedCount; ++i)
            m->setData(selected.at(i), !allFavorite, PlaylistModel::FavoriteRole);
        break;
    }
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

        QList<QUrl> urls = mimeData->urls();
        int dirCount = 0;
        int fileCount = 0;

        for (int i=0; i < urls.count(); ++i)
            (QFileInfo(urls.at(i).toLocalFile()).isDir()) ? dirCount++ : fileCount++;

        MediaDroppedDialog dialog(this);
        dialog.setFileFolderCount(fileCount, dirCount);

        if (!dialog.exec())
            return;

        bool append     = dialog.toAppend();
        bool recursive  = !dialog.root();
        
        QStringList pathList;
        for (int i=0; i < urls.count(); i++) {
            pathList.append(urls.at(i).toLocalFile());
        }

        Player::instance()->folder()->play(pathList, recursive, append);
    }
    
    event->acceptProposedAction();
}

void PlaylistView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    bool indexIsValid = index.isValid();

    QModelIndexList selected = selectedIndexes();
    int selectedCount = selected.count();

    QUrl url = index.data(PlaylistModel::UrlRole).toUrl();

    /////////////////////////////

    QAction playAction("Play", this);
    playAction.setEnabled(selectedCount == 1);

    /////////////////////////////

    QAction playSeveralTimes("Play Several Times", this);
    playSeveralTimes.setEnabled(indexIsValid && selectedCount > 0);

    /////////////////////////////

    bool allFavorite = true;
    for (int i=0; i < selectedCount && allFavorite; ++i) {
        allFavorite = selected.at(i).data(PlaylistModel::FavoriteRole).toBool();
    }

    QString favoritesText = (allFavorite) ? "Remove from Favorites" : "Add to Favorites";
    QAction favoritesAction(favoritesText, this);
    favoritesAction.setEnabled(selectedCount > 0);

    /////////////////////////////

    QAction openFolder("Open Containing Folder", this);

    if (selectedCount == 1) {
        QUrl url = selected.at(0).data(PlaylistModel::UrlRole).toUrl();
        QFileInfo fileInfo(url.toLocalFile());
        openFolder.setEnabled(fileInfo.exists());
    }else{
        openFolder.setEnabled(false);
    }

    /////////////////////////////

    QAction removeAction("Remove", this);
    removeAction.setEnabled(selectedCount > 0);

    /////////////////////////////

    QMenu menu;
    menu.addAction(&playAction);
    menu.addAction(&playSeveralTimes);
    menu.addAction(&favoritesAction);
    menu.addAction(&openFolder);
    menu.addAction(&removeAction);
    menu.addSeparator();
    menu.addAction(m_showFavoritesAction);

    QAction* resultAction = menu.exec(event->globalPos());

    if (selectedCount == 1) {
        QModelIndex index = selected.at(0);

        if (resultAction == &playAction) {
            model()->setData(index, true, PlaylistModel::CurrentRole);
            return;
        }

        if (resultAction == &openFolder) {
            QUrl url = index.data(PlaylistModel::UrlRole).toUrl();
            QFileInfo fileInfo(url.toLocalFile());
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteDir().absolutePath()));
            return;
        }
    }

    if (selectedCount >= 1) {

        if (resultAction == &playSeveralTimes) {
            PlayCountDialog d(this);
            d.setPlayCount(index.data(PlaylistModel::PlayCountRole).toInt());

            int result = d.exec();
            if (result > 0) {
                foreach (QModelIndex index, selected)
                    model()->setData(index, d.playCount(), PlaylistModel::PlayCountRole);
            }
            return;
        }

        if (resultAction == &favoritesAction) {
            foreach (QModelIndex index, selected)
                model()->setData(index, !allFavorite, PlaylistModel::FavoriteRole);
            return;
        }

        if (resultAction == &removeAction) {
            for (int i = selectedCount-1; i >= 0; --i)
                model()->removeRows(selected.at(i).row(), 1);
            return;
        }
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
