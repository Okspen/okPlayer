#include "okplaylistmanager.h"

okPlaylistManager::okPlaylistManager() :
    QList<okPlaylist*>()
{
    current = -1;
}

okPlaylistManager::okPlaylistManager(okPlaylist* i)
{
    current = -1;
    append(i);
}

okPlaylistManager::okPlaylistManager(const okPlaylistManager &l) : QList<okPlaylist*>(l)
{
    current = -1;
}

okPlaylistManager::okPlaylistManager(const QList<okPlaylist*> &l) : QList<okPlaylist*>(l)
{
    current = -1;
}

okPlaylistManager::~okPlaylistManager()
{
    for(int i=0; i<count(); i++)
        delete at(i);
}

void okPlaylistManager::append(const QList<okPlaylist*> &t)
{
    makeCurrentLast();
    QList<okPlaylist*>::append(t);
    current = count()-1;
    emit playlistChanged(currentPlaylist());
}

void okPlaylistManager::append(okPlaylist* t)
{
    makeCurrentLast();
    QList<okPlaylist*>::append(t);
    current = count()-1;
    emit playlistChanged(currentPlaylist());
}

void okPlaylistManager::append(const QStringList &t)
{
    append(new okPlaylist(t));
}

void okPlaylistManager::appendToCurrent(okPlaylist *t)
{
    if(isEmpty()) addPlaylist(t);
    else
    {
        okPlaylist* list = currentPlaylist();
        for(int i=0; i<t->count(); i++)
            list->append(t->at(i));
        delete t;
    }

    emit playlistUpdated();
}

void okPlaylistManager::appendToCurrent(const QStringList &t)
{
    if(isEmpty()) addPlaylist(t);
    else currentPlaylist()->append(t);

    emit playlistUpdated();
}

void okPlaylistManager::addPlaylist(okPlaylist* t)
{
    if(current!=-1 && currentPlaylist()->isEmpty()) appendToCurrent(t);
    else append(t);
}

void okPlaylistManager::addPlaylist(const QStringList& t)
{
    if(current!=-1 && currentPlaylist()->isEmpty()) appendToCurrent(t);
    else append(new okPlaylist(t));
}

okPlaylist* okPlaylistManager::currentPlaylist() const
{
    return (current==-1) ? 0 : at(current);
}

void okPlaylistManager::back()
{
    int index = current-1;
    if(index>=0 && index<count())
    {
        current--;
        emit playlistChanged(currentPlaylist());
    }
}

void okPlaylistManager::forward()
{
    int index = current+1;
    if(index>=0 && index<count())
    {
        current++;
        emit playlistChanged(currentPlaylist());
    }
}

void okPlaylistManager::makeCurrentLast()
{
    int hcount = count();

    if(current < hcount-1) //if current playlist is not the last one
        for(int i=hcount-1; i>current; i--)
        {
            delete at(i);
            removeAt(i);
        }
}
