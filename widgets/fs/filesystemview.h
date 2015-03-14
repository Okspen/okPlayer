#ifndef FSVIEW_H
#define FSVIEW_H

#include <QListView>
#include <QKeyEvent>
#include <QMenu>
#include <QPainter>
#include <QDesktopServices>
#include <QMimeData>
#include "filesystemmodel.h"
#include "player/playersettings.h"

class FileSystemView : public QListView
{
    Q_OBJECT
public:
    explicit FileSystemView(QWidget *parent = 0);
    ~FileSystemView();

    QStringList selectedPathes() const;

signals:
    void open(QModelIndex);
    void play(QStringList pathes, bool recursive = false, bool append = false);
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
    QMenu *multiMenu;

    void initContextMenus();
    void destroyContextMenus();

    QMenu * setupContextMenu();
};

#endif // FSVIEW_H
