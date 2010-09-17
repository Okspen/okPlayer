#ifndef OKPLAYLISTLISTWIDGET_H
#define OKPLAYLISTLISTWIDGET_H

#include <QListWidget>
#include <QDir>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QDebug>

class okPlaylistListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit okPlaylistListWidget(QWidget *parent = 0);

protected:
	void contextMenuEvent(QContextMenuEvent *e);
	void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void updateList();
	void removePlaylist(QModelIndex i);

private:
	QAction* removeAction;

};

#endif // OKPLAYLISTLISTWIDGET_H
