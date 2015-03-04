#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bass/core.h"
#include "trackcycler.h"
#include "playlisthistory.h"
#include "folderplayer.h"
#include "favoritesmanager.h"
#include "medialibrary.h"

class Player : public QObject
{
    Q_OBJECT
public:
    static Player *instance(QObject *parent = 0);
    static void deleteInstance();

    BASS::Core          *audio() const;
    TrackCycler         *cycler() const;
    PlaylistHistory     *history() const;
    FolderPlayer        *folder() const;
    FavoritesManager    *favorites() const;
    MediaLibrary        *media() const;

protected:
    BASS::Core      *m_audio;
    TrackCycler     *m_cycler;
    PlaylistHistory *m_history;
    FolderPlayer    *m_folder;
    FavoritesManager*m_favorites;
    MediaLibrary    *m_media;

private:
    explicit Player(QObject *parent = 0);
    static Player           *m_instance;
};

#endif // PLAYER_H
