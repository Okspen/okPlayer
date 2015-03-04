#include "trackfactory.h"

TrackFactory *TrackFactory::m_instance = NULL;

TrackFactory::TrackFactory()
{
}

TrackFactory *TrackFactory::instance()
{
    if (m_instance == NULL)
        m_instance = new TrackFactory;
    return m_instance;
}

TrackFactory::~TrackFactory()
{
    foreach(const QUrl &key, m_tracks.keys())
        delete m_tracks.value(key);
}

Track *TrackFactory::track(const QUrl &url)
{
    Track *t = m_tracks.value(url);
    if (t != 0) {
        return t;
    } else {
        m_tracks.insert(url, new Track(url));
        return m_tracks.value(url);
    }
}

Track *TrackFactory::clone(Track *track)
{
    Track *t = m_tracks.value(track->url());
    if (t != 0) {
        return t;
    } else {
        m_tracks.insert(track->url(), new Track(*track));
        return m_tracks.value(track->url());
    }
}
