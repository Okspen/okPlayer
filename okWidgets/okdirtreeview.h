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

    QString currentPath();
    void setCurrentPath(const QString& path);
    void setAllowedExtensions(const QStringList& extensions);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void midClicked(QString);
    void newPlaylist(QString, bool);
    void addToPlaylist(QString, bool);

private:
    QAction* appendFileAction;
    QAction* replaceFileAction;
    QAction* appendAllFilesAction;
    QAction* appendRootFilesAction;
    QAction* replaceAllFilesAction;
    QAction* replaceRootFilesAction;

    QFileSystemModel* fsModel;
    QStringList allowedExtensions;
};

#endif // OKDIRTREEVIEW_H
