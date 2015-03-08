#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <QObject>
#include <QHash>
#include <QTimer>
#include <QThread>
#include "mediainfo.h"
#include "tagreader.h"
#include "playlist.h"

class MediaLibrary : public QObject
{
    Q_OBJECT
public:
    explicit MediaLibrary(QObject *parent = 0);
    ~MediaLibrary();

    MediaInfo *info(const QUrl &url);
    void findInfo(Playlist *playlist);

signals:
    void dataChanged(QUrl);
    void queueReady(QList<MediaInfo*>);

private slots:
    void onProcessed(MediaInfo *item);
    void processQueue();

private:
    QHash<QUrl, MediaInfo*> m_info;
    QList<MediaInfo*>       m_queue;
    QTimer                  m_timer;

    QThread     *m_readerThread;
    TagReader   *m_reader;
};

#endif // MEDIALIBRARY_H
