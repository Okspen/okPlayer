#include "okdirtreeview.h"

okDirTreeView::okDirTreeView(QWidget *parent) : QTreeView(parent)
{
	toNewAllFilesAction = new QAction("Replace with all files", this);
	toCurrentAllFilesAction = new QAction("Add all files", this);
	toNewRootFilesAction = new QAction("Replace with root files", this);
	toCurrentRootFilesAction = new QAction("Add root files", this);
}

okDirTreeView::~okDirTreeView()
{
	delete toNewAllFilesAction;
	delete toCurrentAllFilesAction;
	delete toNewRootFilesAction;
	delete toCurrentRootFilesAction;
}

void okDirTreeView::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton)
	{
		emit midClicked(indexAt(event->pos()));
	}
    else QTreeView::mouseReleaseEvent(event);
}

void okDirTreeView::contextMenuEvent(QContextMenuEvent *e)
{
	QModelIndex i = indexAt(e->pos());

	QMenu menu(this);
	menu.addAction(toNewAllFilesAction);
	menu.addAction(toCurrentAllFilesAction);
	menu.addAction(toNewRootFilesAction);
	menu.addAction(toCurrentRootFilesAction);

	QAction* triggeredAction = menu.exec(mapToGlobal(e->pos()));
	if(triggeredAction == 0) return;

	if (triggeredAction == toNewAllFilesAction)
		emit newPlaylist(i, false);
	if(triggeredAction == toCurrentAllFilesAction)
		emit addToPlaylist(i, false);
	if(triggeredAction == toNewRootFilesAction)
		emit newPlaylist(i, true);
	if(triggeredAction == toCurrentRootFilesAction)
		emit addToPlaylist(i, true);
}
