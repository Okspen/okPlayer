#ifndef OKPLAYLISTWIDGET_H
#define OKPLAYLISTWIDGET_H

#include <QTableWidget>
#include <QMouseEvent>
#include <okWidgets/oktablestaritem.h>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QAction>
#include <QMenu>
#include <QDebug>

class okPlaylistWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit okPlaylistWidget(QWidget *parent = 0);
    void fillFromList(const QStringList &newPlaylist, bool append = false);
    void fillFromFavourites();
    void setFavouritesFromFile(const QString& fileName);
    void setSelected(int num);
    void setSelected(QTableWidgetItem* item);
    void starTrack(int row, bool star);
    void removeTrack(int row);

    int getSelected();
    QString fileNameByRow(int row);
    QStringList getPlaylist();
    QStringList getFavouriteTracks();

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

private slots:
    void emitTrackSelected(QModelIndex i);

private:
    QTableWidgetItem* selected;
    QStringList playlist;
    //синхронизирует звездочки из текущего плейлиста и из списка любимых треков
    void updateFavourites();
    void highlight(int row);
    //список любимых треков
    QStringList favouriteTracks;

    void clearList();

    //действия контекстного меню
    QAction* playAction;
    QAction* removeAction;
};

#endif // OKPLAYLISTWIDGET_H
