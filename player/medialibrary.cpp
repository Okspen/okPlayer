#include "medialibrary.h"

MediaLibrary::MediaLibrary(QObject *parent) :
    QObject(parent)
{
    m_reader = 0;
    m_readerThread = 0;
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

    for (int i=0; i<playlist->count(); ++i)
        info(playlist->at(i));
}

void MediaLibrary::onProcessed(MediaInfo *item)
{
    emit dataChanged(item->url());
}

void MediaLibrary::onFinished()
{
    m_reader        = 0;
    m_readerThread  = 0;
}

void MediaLibrary::processQueue()
{
    if (m_queue.isEmpty())
        return;

    if (m_reader != 0)
        m_reader->cancel();

    QThread     *thread = new QThread(this);
    TagReader   *reader = new TagReader;
    reader->moveToThread(thread);
    reader->setList(m_queue);
    m_queue.clear();

    connect(thread, SIGNAL(started()),      reader, SLOT(process()));
    //connect(reader, SIGNAL(finished()),         thread, SLOT(quit()));
    connect(reader, SIGNAL(processed(MediaInfo*)), this, SLOT(onProcessed(MediaInfo*)));
    connect(reader, SIGNAL(finished()),     this,   SLOT(onFinished()));
    connect(reader, SIGNAL(finished()),     reader, SLOT(deleteLater()));
    connect(reader, SIGNAL(finished()),     thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()),     thread, SLOT(deleteLater()));

    thread->start();

    m_reader        = reader;
    m_readerThread  = thread;
}
