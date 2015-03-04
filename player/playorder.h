#ifndef PLAYORDER_H
#define PLAYORDER_H

#include <QObject>
#include "playlist.h"

class PlayOrder : public QObject
{
    Q_OBJECT
public:
    explicit PlayOrder(QObject *parent = 0);
    ~PlayOrder();

    int currentIndex() const;
    void setCurrentIndex(int index);

    bool shuffle() const;
    void setShuffle(bool shuffle);

    Playlist *playlist() const;
    void setPlaylist(Playlist *playlist);

    /* Updates the current playlist shuffle proxy */
    void shuffleTracks();

signals:

public slots:
    void prev();
    void next();
    void rand();

private:
    void shuffleOrder();
    void resetOrder();
    void syncOrder();

    bool        m_shuffle;
    int         m_index;
    Playlist    *m_playlist;
    QList<int>  m_order;

private slots:
    void onCountChanged();
    void onDestroyed();
    void onRemoved(int i, int count);
};

#endif // PLAYORDER_H
