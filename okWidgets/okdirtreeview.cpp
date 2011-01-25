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

    fsModel = new QFileSystemModel;
    fsModel->setRootPath("");
    fsModel->setNameFilterDisables(false);
    setModel(fsModel);
}

okDirTreeView::~okDirTreeView()
{
    delete appendFileAction;
    delete replaceFileAction;
    delete appendAllFilesAction;
    delete appendRootFilesAction;
    delete replaceAllFilesAction;
    delete replaceRootFilesAction;

    delete fsModel;
}

QString okDirTreeView::currentPath()
{
    return fsModel->filePath(currentIndex());
}

void okDirTreeView::setCurrentPath(const QString &path)
{
    setCurrentIndex(fsModel->index(path));
}

void okDirTreeView::setAllowedExtensions(const QStringList& extensions)
{
    fsModel->setNameFilters(extensions);
}

void okDirTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
        emit midClicked(fsModel->filePath(indexAt(event->pos())));
    QTreeView::mouseReleaseEvent(event);
}

void okDirTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit newPlaylist(fsModel->filePath(indexAt(event->pos())), false);
    QTreeView::mouseReleaseEvent(event);
}

void okDirTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex i = indexAt(event->pos());
    QString path = fsModel->filePath(i);

    bool isFile = QFileInfo(path).isFile();

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
        emit newPlaylist(path, false);

    if(triggeredAction==appendAllFilesAction || triggeredAction==appendFileAction)
        emit addToPlaylist(path, false);

    if(triggeredAction==replaceRootFilesAction)
        emit newPlaylist(path, true);

    if(triggeredAction==appendRootFilesAction)
        emit addToPlaylist(path, true);
}
