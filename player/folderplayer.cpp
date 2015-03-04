#include "folderplayer.h"
#include "player/player.h"
#include "player/playersettings.h"

FolderPlayer::FolderPlayer(QObject *parent) :
    QObject(parent)
{
    m_toAppend = false;

    connect(&m_folderScanner, SIGNAL(scanFinished()),   this, SIGNAL(finished()));
    connect(&m_folderScanner, SIGNAL(scanCancelled()),  this, SIGNAL(cancelled()));

    connect(&m_folderScanner, SIGNAL(scanPathChanged(QString)),     this, SIGNAL(scanPathChanged(QString)));
    connect(&m_folderScanner, SIGNAL(fileListReady(QList<QUrl>)),   this, SLOT(onFileListReady(QList<QUrl>)));

    m_folderScanner.setNameFilters(PlayerSettings::nameFilters());
}

FolderPlayer::~FolderPlayer()
{
    m_folderScanner.stop();
    m_folderScanner.quit();
    m_folderScanner.wait();
}

void FolderPlayer::play(const QString &path, bool recursive, bool append)
{
    m_toAppend = append;
    m_folderScanner.generateFileList(path, recursive);
}

void FolderPlayer::play(const QStringList &folderList, bool recursive, bool append)
{
    m_toAppend = append;
    m_folderScanner.generateFileList(folderList, recursive);
}

void FolderPlayer::onFileListReady(const QList<QUrl> &fileList)
{
    PlaylistHistory *history = Player::instance()->history();
    if (m_toAppend) {
        history->addToCurrent(fileList);
    } else {
        history->replaceCurrent(new Playlist(fileList));
    }
}

void FolderPlayer::cancel()
{
    m_folderScanner.stop();
}
