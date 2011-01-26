#include "okplaylistwidget.h"

okPlaylistWidget::okPlaylistWidget(QWidget *parent) :
    QTableWidget(parent)
{
    selected = 0;
    currentPlaylist = -1;

    playAction = new QAction("Play", this);
    removeAction = new QAction("Remove", this);
    openFolderAction = new QAction("Open containing folder", this);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitTrackSelected(QModelIndex)));
    connect(this, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(toggleStarItem(QTableWidgetItem*)));
}

okPlaylistWidget::~okPlaylistWidget()
{
    delete playAction;
    delete removeAction;
    delete openFolderAction;
}

void okPlaylistWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Qt::MouseButton button = event->button();
    if(button == Qt::MidButton)
    {
        int row = indexAt(event->pos()).row();
        removeTrack(row);
    }
    //"back" mouse button
    if(button == Qt::XButton1)
    {
        emit historyBack();
    }
    //"forward" mouse button
    if(button == Qt::XButton2)
    {
        emit historyForward();
    }
    QTableWidget::mouseReleaseEvent(event);
}

void okPlaylistWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Delete)
    {
        QList<QTableWidgetItem*> itemList = selectedItems();
        int count = itemList.count();
        for(int i=0; i<count; i++)
            removeTrack(itemList.at(i)->row());
    }
    if(key == Qt::Key_Left)
    {
        emit historyBack();
    }
    if(key == Qt::Key_Right)
    {
        emit historyForward();
    }
    QTableWidget::keyPressEvent(event);
}

void okPlaylistWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void okPlaylistWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void okPlaylistWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void okPlaylistWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        if(!urlList.at(0).path().mid(1).isEmpty())
            emit droppedMediaToReplace(urlList.at(0).path().mid(1));

        for (int i = 1; i < urlList.count(); i++)
        {
            qDebug() << urlList.at(i).path().mid(1);
            if(!urlList.at(i).path().mid(1).isEmpty())
                emit droppedMediaToAppend(urlList.at(i).path().mid(1));
        }
    }
    else
        qDebug() << "Cannot display data";

    event->acceptProposedAction();
}

void okPlaylistWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex i = indexAt(event->pos());

    QMenu menu(this);

    menu.addAction(playAction);
    menu.addAction(removeAction);
    menu.addAction(openFolderAction);

    QAction* tempAction = menu.exec(mapToGlobal(event->pos()));
    if(tempAction==0) return;

    if(tempAction == playAction)
        emit trackSelected(i.data(Qt::ToolTipRole).toString());

    if(tempAction == removeAction)
        removeTrack(i.row());

    if(tempAction == openFolderAction)
    {
        QString path = QDir::toNativeSeparators(i.data(Qt::ToolTipRole).toString());
        QStringList spath = path.split(QDir::separator());
        spath.removeLast();
        path = spath.join(QDir::separator());
        QDesktopServices::openUrl(QUrl("file:///" + path));
    }
}

void okPlaylistWidget::matchTracks(const QString& query)
{
    int count = rowCount();
    if(query.length() == 0)
    {
        //восстанавливаем состояние виджета на основе плейлиста
        for(int i=0; i<count; i++)
            showRow(i);
        return;
    }

    //выбираем треки, которые подходят и прячем ряд, если трек не подходит
    QString path;
    for(int i=0; i<count; i++)
    {
        path = item(i, 0)->data(Qt::DisplayRole).toString();
        //если в имени файла есть запрашиваемая частица (подстрока)
        if(path.contains(query, Qt::CaseInsensitive))
            showRow(i);
        else hideRow(i);
    }
}

void okPlaylistWidget::changePlaylist(okPlaylist *newPlaylist)
{
    playlist = newPlaylist;
    refresh();
}

void okPlaylistWidget::refresh()
{
    updateFavourites();

    int rowCount = playlist->count();
    setRowCount(rowCount);

    if(rowCount == 0) return;

    selected = 0;
    QTableWidgetItem* tempItem = 0;
    okTableStarItem* tempStar = 0;

    for(int row=0; row<rowCount; row++)
    {
        //создаем новый элемент и делаем, чтобы он не редактировался по двойному клику
        tempItem = new QTableWidgetItem(playlist->at(row).split('/').last());
        tempItem->setFlags(tempItem->flags() & (~Qt::ItemIsEditable));
        tempItem->setData(Qt::ToolTipRole, playlist->at(row));

        tempStar = new okTableStarItem;
        tempStar->setFlags(tempItem->flags() & (~Qt::ItemIsEditable));
        tempStar->setChecked((bool) favouriteTracks->count(playlist->at(row)));

        setItem(row, 0, tempItem);
        //если вставлять после сортировки, то итем вставится не в ряд row,
        //а так, чтобы соответствовать расположению в алфавитном порядке
        setItem(tempItem->row(), 1, tempStar);
    }
}

void okPlaylistWidget::fillFromFavourites()
{
    updateFavourites();
    //replace(*favouriteTracks);
}

void okPlaylistWidget::setFavourites(okPlaylist* newFavourites)
{
    favouriteTracks = newFavourites;
}

void okPlaylistWidget::highlight(int row)
{
    if(row<0 || row>=rowCount()) return;

    scrollToItem(item(row, 0), QAbstractItemView::PositionAtCenter);
    clearSelection();

    QPalette palette;
    int colCount = columnCount();

    if(selected != 0 && selected->row()!=-1)
        for(int i=0; i<colCount; i++)
        {
            item(selected->row(), i)->setBackgroundColor(palette.base().color());
        }

    for(int i=0; i<colCount; i++)
    {
        item(row, i)->setBackgroundColor(palette.color(QPalette::Inactive, QPalette::Highlight));
    }
}

void okPlaylistWidget::toggleStarItem(QTableWidgetItem *tableItem)
{
    if(tableItem->column() == 0) return;
    okTableStarItem* starItem = static_cast<okTableStarItem*>(tableItem);
    starItem->toggle();

    QString fileName = item(tableItem->row(), 0)->data(Qt::ToolTipRole).toString();
    int count = rowCount();
    bool star = starItem->isChecked();
    okTableStarItem* tempStarItem = 0;

    //проходим по всему плейлисту, чтобы все одинаковые файлы тоже были помечены звездочкой
    for(int i=0; i<count; i++)
    {
        if(item(i,0)->data(Qt::ToolTipRole).toString() == fileName)
        {
            tempStarItem = static_cast<okTableStarItem*>(item(i,1));
            tempStarItem->setChecked(star);
        }
    }
}

void okPlaylistWidget::emitTrackSelected(QModelIndex i)
{
    setSelected(item(i.row(), i.column()));
    emit trackSelected(i.data(Qt::ToolTipRole).toString());
}

int okPlaylistWidget::getSelected()
{
    if(selected == 0) return 0;
    return selected->row();
}

QString okPlaylistWidget::fileNameByRow(int row)
{
    if(row<0 || row>=rowCount()) row=0;
    return item(row, 0)->data(Qt::ToolTipRole).toString();
}

okPlaylist* okPlaylistWidget::getPlaylist()
{
    return playlist;
}

okPlaylist* okPlaylistWidget::getFavouriteTracks()
{
    return favouriteTracks;
}

void okPlaylistWidget::setSelected(int num)
{
    setSelected(item(num, 0));
}

void okPlaylistWidget::setSelected(QTableWidgetItem *item)
{
    if(item == 0) return;

    highlight(item->row());
    selected = item;
}

void okPlaylistWidget::removeTrack(int row)
{
    //если мы вдруг удаляем ряд, который сейчас подсвечен, то указатель на элемент этого ряда
    //нужно присвоить нулю, чтобы потом к нему не было обращения
    if((selected != 0) && (row == selected->row())) selected = 0;
    removeRow(row);
    playlist->removeAt(row);
}

void okPlaylistWidget::updateFavourites()
{
    int rowsTotal = rowCount();
    if(rowsTotal == 0) return;

    int itemCount = 0;
    bool checked = false;
    QString tempFileName;
    okTableStarItem* tempStar;

    for(int row=0; row<rowsTotal; row++)
    {
        tempStar = (okTableStarItem*) item(row,1);
        checked = tempStar->isChecked();
        tempFileName = fileNameByRow(row);
        itemCount = favouriteTracks->count(tempFileName);

        //если отмеченная композиция среди любимых треков не встречается, то добавляем
        if(checked && (itemCount == 0))
        {
            favouriteTracks->append(tempFileName);
        }
        //а если была неотмечена и присутствовала в списке, то удаляем
        if(!checked && (itemCount != 0))
        {
            favouriteTracks->removeAll(tempFileName);
        }
    }
    favouriteTracks->removeDuplicates();
}

void okPlaylistWidget::clearList()
{
    updateFavourites();
    setRowCount(0);
    selected = 0;
}
