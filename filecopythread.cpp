#include "filecopythread.h"

FileCopyThread::FileCopyThread(QObject *parent) :
    QThread(parent)
{

}

FileCopyThread::FileCopyThread(
        const QList<QUrl> &files, QString destination, QObject *parent) :
    QThread(parent),
    m_files(files),
    m_destination(destination)
{
    m_stop = false;
}

FileCopyThread::~FileCopyThread()
{
    stop();
}

void FileCopyThread::run()
{
    if (m_files.isEmpty())
        return;

    if (m_destination.isEmpty())
        return;

    m_stop = false;

    QString path;
    QString trackPath;
    QString trackFileName;
    QFileInfo fileInfo;

    for(int i=0; i < m_files.count() && (m_stop == false); i++)
    {
        trackPath       = m_files.at(i).toLocalFile();
        fileInfo.setFile(trackPath);
        trackFileName   = fileInfo.fileName();
        path            = m_destination + "/" + trackFileName;

        QFile::copy(trackPath, path);

        emit copied(i+1);
    }

    if(m_stop == false)
        emit copiedAll();
}

void FileCopyThread::setFileList(const QList<QUrl> &files)
{
    m_files = files;
}

void FileCopyThread::setDestination(const QString &destination)
{
    m_destination = destination;
}

void FileCopyThread::stop()
{
    m_stop = true;
    while(isRunning()) {}
}
