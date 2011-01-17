#include "okdirtreeview.h"
#include <QDebug>

okDirTreeView::okDirTreeView(QWidget *parent) : QTreeView(parent)
{
    appendFileAction = new QAction("Append", this);
    replaceFileAction = new QAction("Replace", this);

    appendAllFilesAction = new QAction("Append all", this);
    appendRootFilesAction = new QAction("Append root", this);
    replaceAllFilesAction = new QAction("Replace with all", this);
    replaceRootFilesAction = new QAction("Replace with root", this);
}

okDirTreeView::~okDirTreeView()
{
    delete appendFileAction;
    delete replaceFileAction;
    delete appendAllFilesAction;
    delete appendRootFilesAction;
    delete replaceAllFilesAction;
    delete replaceRootFilesAction;
}

void okDirTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
        emit midClicked(indexAt(event->pos()));
    else QTreeView::mouseReleaseEvent(event);
}

void okDirTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex i = indexAt(event->pos());
    QFileSystemModel* fsModel = (QFileSystemModel*) model();

    bool isFile = QFileInfo(fsModel->filePath(i)).isFile();

    QMenu menu(this);
    if(isFile)
    {
        menu.addAction(appendFileAction);
        menu.addAction(replaceFileAction);
    }
    else
    {
        menu.addAction(appendAllFilesAction);
        menu.addAction(appendRootFilesAction);
        menu.addAction(replaceAllFilesAction);
        menu.addAction(replaceRootFilesAction);
    }

    QAction* triggeredAction = menu.exec(mapToGlobal(event->pos()));
    if(triggeredAction == 0) return;

    if (triggeredAction==replaceAllFilesAction || triggeredAction==replaceFileAction)
        emit newPlaylist(i, false);

    if(triggeredAction==appendAllFilesAction || triggeredAction==appendFileAction)
        emit addToPlaylist(i, false);

    if(triggeredAction==replaceRootFilesAction)
        emit newPlaylist(i, true);

    if(triggeredAction==appendRootFilesAction)
        emit addToPlaylist(i, true);
}
