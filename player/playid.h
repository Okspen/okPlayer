#ifndef PLAYID_H
#define PLAYID_H

#include "playlist.h"

class PlayId
{
public:
    PlayId();
    PlayId(Playlist *playlist, int index);
    Playlist *playlist() const;

    int index() const;
    void setIndex(int index);

    QUrl url() const;
    bool isValid() const;

    bool operator==(const PlayId& id);
    PlayId operator++();
    PlayId operator--();

private:
    Playlist *m_playlist;
    int m_index;

    bool inRange();
};

#endif // PLAYID_H
