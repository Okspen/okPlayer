#ifndef OKPLAYLISTMANAGER_H
#define OKPLAYLISTMANAGER_H

#include <QList>
#include "okplaylist.h"

class okPlaylistManager : public QObject, public QList<okPlaylist*>
{
    Q_OBJECT
public:
    okPlaylistManager();
    okPlaylistManager(okPlaylist* i);
    okPlaylistManager(const okPlaylistManager &l);
    okPlaylistManager(const QList<okPlaylist*> &l);
    ~okPlaylistManager();

    void append(const QList<okPlaylist*> &t);
    void append(okPlaylist* t);
    void append(const QStringList& t);
    void appendToCurrent(okPlaylist* t);
    void appendToCurrent(const QStringList& t);

    void addPlaylist(okPlaylist* t);
    void addPlaylist(const QStringList& t);

    okPlaylist* currentPlaylist() const;

public slots:
    void back();
    void forward();

signals:
    void playlistUpdated();
    void playlistChanged(okPlaylist*);

private:
    int current;
    //removes all items after current
    void makeCurrentLast();

};

#endif // OKPLAYLISTHISTORY_H
