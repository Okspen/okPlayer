#ifndef DOWNLOADPLAYLISTDIALOG_H
#define DOWNLOADPLAYLISTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include "player/playlist.h"
#include "filecopythread.h"

namespace Ui {
class DownloadPlaylistDialog;
}

class DownloadPlaylistDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DownloadPlaylistDialog(Playlist *playlist, QWidget *parent = 0);
    ~DownloadPlaylistDialog();
    
private:
    Ui::DownloadPlaylistDialog *ui;
    Playlist        *m_playlist;
    FileCopyThread  *m_fileCopyThread;

    void resetUi();
    void freezeUi();
    bool checkDestination(const QString &location);    

private slots:
    void chooseFolder();
    void startDownload();
    void stopDownload();
    void finishDownload();
    void setPlaylistText();
};

#endif // DOWNLOADPLAYLISTDIALOG_H
