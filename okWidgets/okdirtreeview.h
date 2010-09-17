#ifndef OKDIRTREEVIEW_H
#define OKDIRTREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QMenu>

class okDirTreeView : public QTreeView
{
	Q_OBJECT
public:
	okDirTreeView(QWidget *parent);
	~okDirTreeView();
protected:
	void mouseReleaseEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
signals:
	void midClicked(QModelIndex);
	void newPlaylist(QModelIndex, bool);
	void addToPlaylist(QModelIndex, bool);
private:
	QAction* toNewAllFilesAction;
	QAction* toCurrentAllFilesAction;
	QAction* toNewRootFilesAction;
	QAction* toCurrentRootFilesAction;
};

#endif // OKDIRTREEVIEW_H
