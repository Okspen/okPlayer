#ifndef DIRTREEVIEW_H
#define DIRTREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QFileSystemModel>
#include <QMenu>
#include <QPainter>
#include <QDesktopServices>
#include <QShortcut>
#include "player/player.h"
#include "player/playersettings.h"
#include <QDebug>

class DirTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit DirTreeView(QWidget *parent);
    ~DirTreeView();

    void paintEvent(QPaintEvent *event);
    QString currentPath() const;
    void setCurrentPath(const QString &path);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    QAction *appendFileAction;
    QAction *replaceFileAction;
    QAction *appendAllFilesAction;
    QAction *appendRootFilesAction;
    QAction *replaceAllFilesAction;
    QAction *replaceRootFilesAction;
    QAction *openFolderAction;

    QFileSystemModel    *m_fsModel;
    QStringList         m_allowedExtensions;
    QString             m_currentPath;

    void readSettings();
    void writeSettings();

};

#endif // DIRTREEVIEW_H
