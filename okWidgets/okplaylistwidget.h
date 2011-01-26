#ifndef OKPLAYLISTWIDGET_H
#define OKPLAYLISTWIDGET_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include "okplaylist.h"
#include "okWidgets/oktablestaritem.h"

#include <QDebug>

class okPlaylistWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit okPlaylistWidget(QWidget *parent = 0);
    ~okPlaylistWidget();

    void fillFromFavourites();
    void setFavourites(okPlaylist* newFavourites);
    void setSelected(int num);
    void setSelected(QTableWidgetItem* item);
    void removeTrack(int row);

    int getSelected();
    QString fileNameByRow(int row);
    okPlaylist* getPlaylist();
    okPlaylist* getFavouriteTracks();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void midClicked(const QModelIndex& i);
    void trackSelected(const QString& trackPath);
    void droppedMediaToAppend(const QString& path);
    void droppedMediaToReplace(const QString& path);

    void historyBack();
    void historyForward();

public slots:
    //ищет в именах треков в плейлисте подстроки query и показывает только найденные файлы
    void matchTracks(const QString& query);
    void refresh();
    void changePlaylist(okPlaylist* newPlaylist);

private slots:
    void emitTrackSelected(QModelIndex i);
    //тогглит элемент отображающий состояние "в избранном"
    void toggleStarItem(QTableWidgetItem *tableItem);

private:
    int currentPlaylist;
    QTableWidgetItem* selected;
    //current playlist pointer
    okPlaylist* playlist;
    //list of favourite tracks
    okPlaylist* favouriteTracks;

    //item context menu actions
    QAction* playAction;
    QAction* removeAction;
    QAction* openFolderAction;

    //синхронизирует звездочки из текущего плейлиста и из списка любимых треков
    void updateFavourites();
    void highlight(int row);
    void clearList();
};

#endif // OKPLAYLISTWIDGET_H
