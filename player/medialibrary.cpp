#include "medialibrary.h"

MediaLibrary::MediaLibrary(QObject *parent) :
    QObject(parent)
{    
    m_readerThread = new QThread(this);

    qRegisterMetaType< QList<MediaInfo *> >("QList<MediaInfo *>");

    m_reader = new TagReader;
    m_reader->moveToThread(m_readerThread);
    connect(this,       SIGNAL(queueReady(QList<MediaInfo*>)),  m_reader,   SLOT(process(QList<MediaInfo*>)),   Qt::QueuedConnection);
    connect(m_reader,   SIGNAL(processed(MediaInfo*)),          this,       SLOT(onProcessed(MediaInfo*)),      Qt::QueuedConnection);

    m_readerThread->start();

    m_timer.setSingleShot(true);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(processQueue()));
}

MediaLibrary::~MediaLibrary()
{
    if (m_reader != 0)
        m_reader->cancel();

    if (m_readerThread != 0) {
        m_readerThread->quit();
        m_readerThread->wait();
    }

    qDeleteAll(m_info);
}

MediaInfo *MediaLibrary::info(const QUrl &url)
{
    if (m_info.contains(url))
        return m_info.value(url);

    MediaInfo *info = new MediaInfo(url);
    m_info.insert(url, info);

    m_queue.append(info);
    m_timer.start(200);

    return m_info.value(url);
}

void MediaLibrary::findInfo(Playlist *playlist)
{
    if (playlist==0 || playlist->isEmpty())
        return;

    for (int i=0; i < playlist->count(); ++i)
        info(playlist->at(i));
}

void MediaLibrary::onProcessed(MediaInfo *item)
{
    emit dataChanged(item->url());
}

void MediaLibrary::processQueue()
{
    if (m_queue.isEmpty())
        return;

    emit queueReady(m_queue);

    m_queue.clear();
}
