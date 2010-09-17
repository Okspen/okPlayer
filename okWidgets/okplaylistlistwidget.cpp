#include "okplaylistlistwidget.h"

okPlaylistListWidget::okPlaylistListWidget(QWidget *parent) :
    QListWidget(parent)
{
	removeAction = new QAction("Remove", this);
	updateList();
}

void okPlaylistListWidget::updateList()
{
	QString playlistFolder = QApplication::applicationDirPath() + "/playlists";
	QDir navigator(playlistFolder);
	QList<QString> entries = navigator.entryList();

	int count = entries.count();
	QString item;
	QListWidgetItem* tempItem=0;

	clear();
	for(int i=0; i<count; i++)
	{
		item = entries.at(i);

		if((item != ".") && (item != ".."))
		{
			tempItem = new QListWidgetItem(item.left(item.length()-4));
			tempItem->setData(Qt::UserRole, playlistFolder + "/" + item);

			insertItem(i, tempItem);
		}
	}
}

void okPlaylistListWidget::contextMenuEvent(QContextMenuEvent *e)
{
	QModelIndex i = indexAt(e->pos());
	//если нажали в пустом месте, то меню не нужно
	if(i.row() == -1) return;

	QMenu* menu = new QMenu(this);
	menu->addAction(removeAction);

	QAction* triggeredAction = menu->exec(mapToGlobal(e->pos()));
	if(triggeredAction != 0)
	{
		if(triggeredAction == removeAction)
		{
			removePlaylist(i);
			updateList();
		}
	}
}

void okPlaylistListWidget::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Delete)
	{
		QModelIndexList indexList = selectedIndexes();
		int count = indexList.count();
		for(int i=0; i<count; i++)
			removePlaylist(indexList.at(i));

		updateList();
	}
}

void okPlaylistListWidget::removePlaylist(QModelIndex i)
{
	QFile::remove(i.data(Qt::UserRole).toString());
}
