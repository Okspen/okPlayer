#ifndef FSVIEW_H
#define FSVIEW_H

#include <QListView>
#include <QKeyEvent>
#include <QMenu>
#include <QPainter>
#include <QDesktopServices>
#include "filesystemmodel.h"
#include "player/playersettings.h"

class FileSystemView : public QListView
{
    Q_OBJECT
public:
    explicit FileSystemView(QWidget *parent = 0);
    ~FileSystemView();

signals:
    void open(QModelIndex);
    void up();

protected:
    void keyReleaseEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QAction *appendAction;
    QAction *replaceAction;
    QAction *appendAllAction;
    QAction *appendRootAction;
    QAction *replaceAllAction;
    QAction *replaceRootAction;
    QAction *addToFavorites;
    QAction *openFolderAction;

    QMenu *fileMenu;
    QMenu *dirMenu;

    void initContextMenus();
    void destroyContextMenus();
};

#endif // FSVIEW_H
