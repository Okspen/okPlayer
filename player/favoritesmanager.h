#ifndef FAVORITESMANAGER_H
#define FAVORITESMANAGER_H

#include <QObject>
#include "player/playlist.h"

class FavoritesManager : public QObject
{
    Q_OBJECT
public:
    explicit FavoritesManager(QObject *parent = 0);
    ~FavoritesManager();

    void setFavorites(const QList<QUrl> &urls);
    const Playlist *playlist() const;
    bool isFavorite(const QUrl &url) const;
    
signals:
    void added(const QUrl &url);
    void removed(const QUrl &url);
    
public slots:
    void add(const QUrl &url);
    void remove(const QUrl &url);

protected:
    Playlist *m_favorites;
    
};

#endif // FAVORITESMANAGER_H
