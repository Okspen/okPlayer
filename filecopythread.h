#ifndef FILECOPYTHREAD_H
#define FILECOPYTHREAD_H

#include <QThread>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include "player/playlist.h"

class FileCopyThread : public QThread
{
    Q_OBJECT
public:
    explicit FileCopyThread(QObject *parent = 0);
    explicit FileCopyThread(const QList<QUrl> &files, QString destination, QObject *parent = 0);
    ~FileCopyThread();
    void run();
    void setFileList(const QList<QUrl> &files);
    void setDestination(const QString &destination);

signals:
    void copied(int);
    void copiedAll();
    
public slots:
    void stop();

private:
    QList<QUrl> m_files;
    QString     m_destination;
    bool        m_stop;
};

#endif // FILECOPYTHREAD_H
