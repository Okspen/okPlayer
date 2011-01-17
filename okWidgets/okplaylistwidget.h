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
    void append(okPlaylist* newPlaylist);
    void append(const QStringList& newPlaylist);
    void replace(okPlaylist* newPlaylist);
    void replace(const QStringList& newPlaylist);
    void refresh();
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
    void midClicked(QModelIndex i);
    void trackSelected(const QString& trackPath);
    void droppedMediaToAppend(const QString& path);
    void droppedMediaToReplace(const QString& path);

public slots:
    //ищет в именах треков в плейлисте подстроки query и показывает только найденные файлы
    void matchTracks(QString query);

private slots:
    void emitTrackSelected(QModelIndex i);
    //тогглит элемент отображающий состояние "в избранном"
    void toggleStarItem(QTableWidgetItem *tableItem);

private:
    int currentPlaylist;
    QTableWidgetItem* selected;
    //список любимых треков
    okPlaylist* favouriteTracks;
    //история плейлистов
    QList<okPlaylist*> playlistHistory;

    //действия контекстного меню
    QAction* playAction;
    QAction* removeAction;
    QAction* openFolderAction;

    //синхронизирует звездочки из текущего плейлиста и из списка любимых треков
    void updateFavourites();
    void highlight(int row);
    void clearList();
    void makeCurrentLast();

    void navigateHistoryBack();
    void navigateHistoryForward();
};

#endif // OKPLAYLISTWIDGET_H
