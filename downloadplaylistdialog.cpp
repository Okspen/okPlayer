#include "downloadplaylistdialog.h"
#include "ui_downloadplaylistdialog.h"

DownloadPlaylistDialog::DownloadPlaylistDialog(Playlist *playlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadPlaylistDialog),
    m_playlist(playlist)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);

    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    if (!defaultPath.isEmpty())
        ui->destinationEdit->setText(defaultPath);

    m_fileCopyThread = new FileCopyThread(this);
    connect(m_fileCopyThread, SIGNAL(copied(int)), ui->progressBar, SLOT(setValue(int)));
    connect(m_fileCopyThread, SIGNAL(copiedAll()), this,            SLOT(finishDownload()));

    connect(ui->chooseButton,   SIGNAL(clicked()),      this,       SLOT(chooseFolder()));
    connect(ui->startButton,    SIGNAL(clicked()),      this,       SLOT(startDownload()));
    connect(ui->stopButton,     SIGNAL(clicked()),      this,       SLOT(stopDownload()));
    connect(ui->cancelButton,   SIGNAL(clicked()),      this,       SLOT(close()));

    resetUi();

    if (m_playlist == 0 || m_playlist->isEmpty())
        ui->startButton->setEnabled(false);
    else
        setPlaylistText();

    connect(m_playlist, SIGNAL(countChanged()), this, SLOT(setPlaylistText()));

    setFixedSize(width(), height());
}

DownloadPlaylistDialog::~DownloadPlaylistDialog()
{
    delete ui;
}

void DownloadPlaylistDialog::resetUi()
{
    ui->destinationLabel->setEnabled(true);
    ui->chooseButton->setEnabled(true);
    ui->destinationEdit->setEnabled(true);

    ui->progressBar->setMaximum(1);
    ui->progressBar->reset();

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    ui->startButton->show();
    ui->stopButton->hide();
}

void DownloadPlaylistDialog::freezeUi()
{
    ui->destinationLabel->setEnabled(false);
    ui->chooseButton->setEnabled(false);
    ui->destinationEdit->setEnabled(false);

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    ui->startButton->hide();
    ui->stopButton->show();
}

bool DownloadPlaylistDialog::checkDestination(const QString &location)
{
    QFileInfo d(location);
    return d.exists() && d.isDir() && d.isReadable();
}

void DownloadPlaylistDialog::setPlaylistText()
{
    QString text;
    int count = m_playlist->count();
    int uniqueCount = m_playlist->uniqueCount();

    if (count == uniqueCount) {
        text = QString("Playlist of %1 tracks (all unique)").arg(count);
    } else {
        text = QString("Playlist of %1 tracks (%2 unique files)").arg(count).arg(uniqueCount);
    }

    ui->playlistLabel->setText(text);
}

void DownloadPlaylistDialog::chooseFolder()
{
    QFileDialog fileDialog(this, "Select Directory");
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::DirectoryOnly);
    fileDialog.setDirectory(ui->destinationEdit->text());

    if (!fileDialog.exec())
        return;

    ui->destinationEdit->setText(fileDialog.selectedFiles().first());
}

void DownloadPlaylistDialog::startDownload()
{
    if (m_playlist == 0 || m_playlist->isEmpty()) {
        QMessageBox::warning(this, "Error", "Playlist is empty. Nothing to copy!");
        return;
    }

    QString location = ui->destinationEdit->text();
    if (!checkDestination(location)) {
        QMessageBox::warning(this, "Error", "Can't copy to current location");
        return;
    }

    freezeUi();

    m_fileCopyThread->setFileList(m_playlist->uniqueUrls());
    m_fileCopyThread->setDestination(location);

    ui->progressBar->setMaximum(m_playlist->count());

    m_fileCopyThread->start();
    m_fileCopyThread->setPriority(QThread::LowestPriority);
}

void DownloadPlaylistDialog::stopDownload()
{
    m_fileCopyThread->stop();
    resetUi();
}

void DownloadPlaylistDialog::finishDownload()
{
    QMessageBox::information(this, "Copying Finished", "Playlist has been succesfully copied!");
    close();
}
