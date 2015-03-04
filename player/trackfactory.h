#ifndef TRACKFACTORY_H
#define TRACKFACTORY_H

#include <QHash>
#include <QJsonObject>
#include "player/track.h"

class TrackFactory
{
public:
    static TrackFactory* instance();
    ~TrackFactory();
    Track *track(const QUrl& url);
    Track *clone(Track *track);

private:
    explicit TrackFactory();
    QHash<QUrl, Track*> m_tracks;
    static TrackFactory *m_instance;

};

#endif // LOCALTRACKFACTORY_H
