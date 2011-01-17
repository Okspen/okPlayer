#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dirPlaylistSplitter = new QSplitter(Qt::Vertical, ui->centralWidget);
    dirPlaylistSplitter->addWidget(ui->playlistWidget);
    dirPlaylistSplitter->addWidget(ui->dirTree);
    ui->splitterLayout->addWidget(dirPlaylistSplitter);

    findInPlaylist = new QShortcut(QKeySequence::Find, this);
    connect(findInPlaylist, SIGNAL(activated()), this, SLOT(toggleSearchVisibility()));

    ui->searchWidget->hide();

    player = new okPlayer;
    player->setPlaylistWidget(ui->playlistWidget);
    player->setTreeWidget(ui->dirTree);
    player->setSeekSlider(ui->sliderSeek);

    ui->timeLabel->setVLC(player->getVLCWrapper());

    setConnections();
    restoreSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete player;
    delete findInPlaylist;
    delete dirPlaylistSplitter;
    delete ui;
}

void MainWindow::setConnections()
{
    connect(ui->buttonStop, SIGNAL(clicked()), player, SLOT(stop()));
    connect(ui->buttonPause, SIGNAL(clicked()), player, SLOT(pause()));
    connect(ui->buttonPlay, SIGNAL(clicked()), player, SLOT(play()));
    connect(ui->buttonPrev, SIGNAL(clicked()), player, SLOT(prev()));
    connect(ui->buttonNext, SIGNAL(clicked()), player, SLOT(next()));
    connect(ui->buttonRandom, SIGNAL(clicked()), player, SLOT(playRandom()));

    connect(ui->dirTree, SIGNAL(doubleClicked(QModelIndex)), player, SLOT(newPlaylistFromIndex(QModelIndex)));
    connect(ui->dirTree, SIGNAL(midClicked(QModelIndex)), player, SLOT(addToPlaylistFromIndex(QModelIndex)));
    connect(ui->dirTree, SIGNAL(newPlaylist(QModelIndex, bool)), player, SLOT(newPlaylistFromIndex(QModelIndex, bool)));
    connect(ui->dirTree, SIGNAL(addToPlaylist(QModelIndex, bool)), player, SLOT(addToPlaylistFromIndex(QModelIndex, bool)));

    connect(ui->sliderVolume, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));

    connect(ui->fieldQuickSearch, SIGNAL(textChanged(QString)), ui->playlistWidget, SLOT(matchTracks(QString)));

    connect(ui->playlistWidget, SIGNAL(itemClicked(QTableWidgetItem*)), player, SLOT(toggleTableStarItem(QTableWidgetItem*)));
    connect(ui->playlistWidget, SIGNAL(droppedMediaToReplace(QString)), player, SLOT(newPlaylistFromPath(QString)));
    connect(ui->playlistWidget, SIGNAL(droppedMediaToAppend(QString)), player, SLOT(addToPlaylistFromPath(QString)));
    connect(ui->playlistWidget, SIGNAL(trackSelected(QString)), player, SLOT(play(QString)));

    //кнопки открытия и сохранения плейлистов
    connect(ui->buttonCopyPlaylist, SIGNAL(clicked()), this, SLOT(copyPlaylist()));
    connect(ui->buttonLoadFavorites, SIGNAL(clicked()), this, SLOT(loadFavorites()));

    connect(ui->actionAlways_on_top, SIGNAL(toggled(bool)), this, SLOT(toggleOnTop(bool)));
    connect(ui->actionMusic_browser, SIGNAL(triggered()), this, SLOT(openMusicBrowser()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelp()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));

    connect(ui->actionPlaylist, SIGNAL(toggled(bool)), ui->playlistWidget, SLOT(setVisible(bool)));
    connect(ui->actionDirectory_tree, SIGNAL(toggled(bool)), ui->dirTree, SLOT(setVisible(bool)));

    //connect(ui->reset, SIGNAL(clicked()), this, SLOT(refreshFileSystem()));

    connect(ui->playModeBox, SIGNAL(currentIndexChanged(int)), player, SLOT(setPlayingModeState(int)));
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    switch (event->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::toggleOnTop(bool checked)
{
    if(checked) setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    else setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();
}

void MainWindow::toggleSearchVisibility()
{
    ui->searchWidget->setVisible(!ui->searchWidget->isVisible());
}

void MainWindow::showAboutDialog()
{
    aboutDialog about(this);
    about.exec();
}

void MainWindow::saveSettings()
{
    ui->playlistWidget->getPlaylist()->writeToFile("current.m3u");
    //перед выходом нужно сохранить избранное
    player->writeFavouritesToFile();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");
    settings.setValue("player/volume", player->getVolume());
    settings.setValue("player/playlist", "current.m3u");
    settings.setValue("player/currentTrack", ui->playlistWidget->getSelected());

    settings.setValue("player/playingMode", player->getPlayingMode());

    settings.setValue("dirTree/currentPath", player->getFSPath());

    settings.setValue("playlist/visible", ui->playlistWidget->isVisibleTo(this));
    settings.setValue("dirTree/visible", ui->dirTree->isVisibleTo(this));

    settings.setValue("mainwindow/geometry", saveGeometry());
    settings.setValue("dirPlaylistSplitter/geometry", dirPlaylistSplitter->saveState());
}

void MainWindow::restoreSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");
    bool* ok = false;

    player->setVolume(settings.value("player/volume").toInt(ok));
    ui->sliderVolume->setValue(player->getVolume());

    ui->playlistWidget->setFavourites(new okPlaylist(QCoreApplication::applicationDirPath()+"/favourites.m3u"));

    player->restorePlaylist(settings.value("player/playlist").toString());
    ui->playlistWidget->setSelected(settings.value("player/currentTrack").toInt());
    player->playCurrent();

    player->setPlayingModeState(settings.value("player/playingMode").toInt());
    ui->playModeBox->setCurrentIndex(settings.value("player/playingMode").toInt());

    bool dirTreeVisible = settings.value("dirTree/visible").toBool();
    bool playlistVisible = settings.value("playlist/visible").toBool();
    if(!settings.contains("dirTree/visible")) dirTreeVisible = true;
    if(!settings.contains("playlist/visible")) playlistVisible = true;

    ui->dirTree->setCurrentIndex(player->getIndexFromPath(settings.value("dirTree/currentPath").toString()));
    ui->dirTree->setVisible(dirTreeVisible);

    ui->playlistWidget->setVisible(playlistVisible);

    ui->actionPlaylist->setChecked(dirTreeVisible);
    ui->actionDirectory_tree->setChecked(playlistVisible);

    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    dirPlaylistSplitter->restoreState(settings.value("dirPlaylistSplitter/sizes").toByteArray());
}

void MainWindow::openPlaylist()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Playlist"), "", tr("Playlist (*.m3u)"));
    ui->playlistWidget->replace(new okPlaylist(fileName));
}

void MainWindow::savePlaylist()
{
    savedialog dialog(this);
    if(dialog.exec() == 1)
    ui->playlistWidget->getPlaylist()->writeToFile(dialog.fileName());
}

void MainWindow::copyPlaylist()
{
    QFileDialog fileDialog(this, "Select directory");
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);
    if(!fileDialog.exec()) return;

    QString path;
    QString dir = fileDialog.selectedFiles().first();
    okPlaylist* playlist = ui->playlistWidget->getPlaylist();

    int numFiles = playlist->count();
    QProgressDialog progress("Copying files...", "Abort", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);

    for(int i=0; i<numFiles; i++)
    {
        progress.setValue(i);
        if(progress.wasCanceled()) break;

        path = dir+"/"+playlist->at(i).split("/").last();
        QFile::copy(playlist->at(i), path);
    }
    progress.setValue(numFiles);
}

void MainWindow::loadFavorites()
{
    ui->playlistWidget->fillFromFavourites();
}

void MainWindow::openHelp()
{
    QDesktopServices::openUrl("file:///" + QApplication::applicationDirPath() + "/help/index.html");
}

void MainWindow::openMusicBrowser()
{
    dbBrowser musicBrowser(this);
    musicBrowser.setDb(player->getDb());
    musicBrowser.exec();
}

void MainWindow::refreshFileSystem()
{
}
