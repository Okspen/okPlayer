#ifndef OKDIRTREEVIEW_H
#define OKDIRTREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QFileSystemModel>
#include <QMenu>

class okDirTreeView : public QTreeView
{
    Q_OBJECT
public:
    okDirTreeView(QWidget *parent);
    ~okDirTreeView();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void midClicked(QModelIndex);
    void newPlaylist(QModelIndex, bool);
    void addToPlaylist(QModelIndex, bool);

private:
    QAction* appendFileAction;
    QAction* replaceFileAction;
    QAction* appendAllFilesAction;
    QAction* appendRootFilesAction;
    QAction* replaceAllFilesAction;
    QAction* replaceRootFilesAction;
};

#endif // OKDIRTREEVIEW_H
