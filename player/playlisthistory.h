#ifndef PLAYLISTHISTORY_H
#define PLAYLISTHISTORY_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include "player/playlist.h"

class PlaylistHistory : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistHistory(QObject *parent=0);
    ~PlaylistHistory();
    QList<Playlist *> *playlists() const;
    Playlist *current() const;
    int currentIndex() const;

signals:
    void currentChanged(Playlist*);
    void countChanged();

public slots:
    void prev();
    void next();
    void addToCurrent(const QList<QUrl> &filelist);
    void replaceCurrent(Playlist *playlist);
    void switchPlaylist(int index);
    void deleteCurrentPlaylist();

private:
    QList<Playlist*>    *m_playlists;
    int                 m_playlistId;
    int                 m_currentIndex;

    bool inRange(int index) const;
};

#endif // PLAYLISTHISTORY_H
