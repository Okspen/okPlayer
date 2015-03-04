#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include "player/player.h"
#include "historymodel.h"

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HistoryWidget(QWidget *parent = 0);
    ~HistoryWidget();

signals:
    void playlistChanged(int);
    void indexConverted(int);
    
private:
    Ui::HistoryWidget *ui;
    HistoryModel    *m_model;
    PlaylistHistory *m_history;

private slots:
    void onPlaylistChanged(Playlist *playlist);
    void onCountChanged();
    void onCurrentIndexChanged(int index);
};

#endif // HISTORYWIDGET_H
