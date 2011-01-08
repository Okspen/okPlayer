#include "okplaylistwidget.h"

okPlaylistWidget::okPlaylistWidget(QWidget *parent) :
    QTableWidget(parent)
{
    selected = 0;

    playAction = new QAction("Play", this);
    removeAction = new QAction("Remove", this);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitTrackSelected(QModelIndex)));
}

void okPlaylistWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        int row = indexAt(event->pos()).row();
        //если мы вдруг удаляем ряд, который сейчас подсвечен, то указатель на элемент этого ряда
        //нужно присвоить нулю, чтобы потом к нему не было обращения
        if((selected != 0) && (row == selected->row())) selected = 0;
        removeRow(row);
    }
    QTableWidget::mouseReleaseEvent(event);
}

void okPlaylistWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        QList<QTableWidgetItem*> itemList = selectedItems();
        int count = itemList.count();
        for(int i=0; i<count; i++)
            removeTrack(itemList.at(i)->row());
    }
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
    {
        qDebug() << "Cannot display data";
    }

    event->acceptProposedAction();
}

void okPlaylistWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex i = indexAt(event->pos());

    QMenu menu(this);

    menu.addAction(playAction);
    menu.addAction(removeAction);

    QAction* tempAction = menu.exec(mapToGlobal(event->pos()));
    if(tempAction==0) return;

    if(tempAction == playAction)
        emit trackSelected(i.data(Qt::ToolTipRole).toString());

    if(tempAction == removeAction)
        removeTrack(i.row());
}

void okPlaylistWidget::fillFromList(const QStringList &newPlaylist, bool append)
{
    if(newPlaylist.empty()) return;
    int startRow = rowCount();
    if(!append)
    {
        startRow = 0;
        selected = 0;
        playlist = newPlaylist;
    }
    else playlist.append(newPlaylist);

    int needRows = playlist.count();
    setRowCount(needRows);

    QTableWidgetItem* tempItem = 0;
    okTableStarItem* tempStar = 0;

    for(int row=startRow; row<(needRows); row++)
    {
        //создаем новый элемент и делаем, чтобы он не редактировался по двойному клику
        tempItem = new QTableWidgetItem(playlist.at(row).split('/').last());
        tempItem->setFlags(tempItem->flags() & (~Qt::ItemIsEditable));
        tempItem->setData(Qt::ToolTipRole, playlist.at(row));

        tempStar = new okTableStarItem;
        tempStar->setFlags(tempItem->flags() & (~Qt::ItemIsEditable));
        tempStar->setChecked((bool) favouriteTracks.count(playlist.at(row)));

        setItem(row, 0, tempItem);
        //если вставлять после сортировки, то итем вставится не в ряд row,
        //а так, чтобы соответствовать расположению в алфавитном порядке
        setItem(tempItem->row(), 1, tempStar);
    }
}

void okPlaylistWidget::fillFromFavourites()
{
	updateFavourites();
	fillFromList(favouriteTracks);
}

void okPlaylistWidget::setFavouritesFromFile(const QString& fileName)
{
	QFile file(fileName);
	//файл больше 3мб открывать опасно - плеер может упасть
	if(file.size() > 3*1000*1000)
	{
		qDebug() << "favourites.m3u is too big";
		return;
	}

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

	QTextStream textstr(&file);
	textstr.setCodec("UTF-8");
	while(!textstr.atEnd())
            favouriteTracks << textstr.readLine();

	file.close();
}

void okPlaylistWidget::highlight(int row)
{
    if(row<0 || row>=rowCount()) return;

    scrollToItem(item(row, 0), QAbstractItemView::PositionAtCenter);
    clearSelection();

    QPalette palette;
    int colCount = columnCount();

    if(selected != 0)
        for(int i=0; i<colCount; i++)
        {
            if(selected->row() != -1)
                item(selected->row(), i)->setBackgroundColor(palette.base().color());
        }

    for(int i=0; i<colCount; i++)
    {
        item(row, i)->setBackgroundColor(palette.color(QPalette::Inactive, QPalette::Highlight));
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

QStringList okPlaylistWidget::getPlaylist()
{
    return playlist;
}

QStringList okPlaylistWidget::getFavouriteTracks()
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

void okPlaylistWidget::starTrack(int row, bool star)
{
    QString fileName = item(row, 0)->data(Qt::ToolTipRole).toString();
    int count = rowCount();
    okTableStarItem* tempStarItem = 0;

    for(int i=0; i<count; i++)
    {
        if(item(i,0)->data(Qt::ToolTipRole).toString() == fileName)
        {
            tempStarItem = (okTableStarItem*) item(i,1);
            tempStarItem->setChecked(star);
        }
    }
}

void okPlaylistWidget::removeTrack(int row)
{
    if((selected != 0) && (row == selected->row())) selected = 0;
    removeRow(row);
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
        itemCount = favouriteTracks.count(tempFileName);

        //если отмеченная композиция среди любимых треков не встречается, то добавляем
        if(checked && (itemCount == 0))
        {
            favouriteTracks << tempFileName;
        }
        //а если была неотмечена и присутствовала в списке, то удаляем
        if(!checked && (itemCount != 0))
        {
            favouriteTracks.removeAll(tempFileName);
        }
    }
}

void okPlaylistWidget::clearList()
{
    updateFavourites();
	setRowCount(0);
	selected = 0;
}
