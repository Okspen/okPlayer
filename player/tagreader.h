#ifndef TAGREADER_H
#define TAGREADER_H

#include <QObject>
#include <QFileInfo>
#include <QTextCodec>
#include <QThread>
#include <QDebug>
#include "mediainfo.h"

#include "tags/c/tags.h"
#include "bass/localstream.h"

class TagReader : public QObject
{
    Q_OBJECT
public:
    explicit TagReader(QObject *parent = 0);
    void setList(QList<MediaInfo*> list);

public slots:
    void process();
    void cancel();

private:
    bool                m_cancel;
    QList<MediaInfo*>   m_queue;

    void readTags(MediaInfo *info);
    void readTagsBASS(MediaInfo *info);

signals:
    void processed(MediaInfo *item);
    void finished();
};

#endif // TAGREADER_H
