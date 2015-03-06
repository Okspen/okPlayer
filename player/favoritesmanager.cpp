#include "favoritesmanager.h"
#include "player.h"
#include "player/playersettings.h"

FavoritesManager::FavoritesManager(QObject *parent) :
    QObject(parent)
{
    m_favorites = new Playlist(this);
}

FavoritesManager::~FavoritesManager()
{
    delete m_favorites;
}

void FavoritesManager::setFavorites(const QList<QUrl> &urls)
{
    m_favorites->append(urls);
}

const Playlist *FavoritesManager::playlist() const
{
    return m_favorites;
}

bool FavoritesManager::isFavorite(const QUrl &url) const
{
    return m_favorites->contains(url);
}

void FavoritesManager::add(const QUrl &url)
{
    if (isFavorite(url))
        return;

    m_favorites->append(url);
    emit added(url);
}

void FavoritesManager::remove(const QUrl &url)
{
    if (!isFavorite(url))
        return;

    m_favorites->removeAt(m_favorites->indexOf(url));
    emit removed(url);
}
