#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_player = Player::instance();

    ui->setupUi(this);

    createShortcuts();
    setConnections();

    initAudioUI();
    initCyclerUI();
    initOrientation();

    readSettings();

    // Autosave every 20 minutes
    QTimer* writeSettingsTimer = new QTimer(this);
    connect(writeSettingsTimer, SIGNAL(timeout()), this, SLOT(writeSettings()));
    writeSettingsTimer->start(20 * 60 * 1000);
}

MainWindow::~MainWindow()
{
    writeSettings();

    delete ui;
    Player::deleteInstance();
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

void MainWindow::createShortcuts()
{
    /* Audio shortcuts */

    BASS::Core *audio = m_player->audio();
    if (audio != 0) {

        playShortcut = new QShortcut(Qt::Key_MediaPlay, this);
        connect(playShortcut,       SIGNAL(activated()),    audio, SLOT(togglePlayPause()));

        playPauseShortcut = new QShortcut(Qt::Key_MediaTogglePlayPause, this);
        connect(playPauseShortcut,  SIGNAL(activated()),    audio, SLOT(togglePlayPause()));

        pauseShortcut = new QShortcut(Qt::Key_MediaPause, this);
        connect(pauseShortcut,      SIGNAL(activated()),    audio, SLOT(pause()));

        volumeUpShortcut = new QShortcut(Qt::Key_Plus, this);
        connect(volumeUpShortcut,   SIGNAL(activated()),    audio,  SLOT(volumeUp()));

        volumeDownShortcut = new QShortcut(Qt::Key_Minus, this);
        connect(volumeDownShortcut, SIGNAL(activated()),    audio,  SLOT(volumeDown()));
    }

    /* Cycler shortcuts */

    TrackCycler *cycler = m_player->cycler();
    if (cycler != 0) {

        nextShortcut = new QShortcut(Qt::Key_MediaNext, this);
        connect(nextShortcut,   SIGNAL(activated()),    cycler, SLOT(next()), Qt::UniqueConnection);

        previousShortcut = new QShortcut(Qt::Key_MediaPrevious, this);
        connect(previousShortcut,SIGNAL(activated()),   cycler, SLOT(prev()), Qt::UniqueConnection);
    }

    /* History shortcuts */

    PlaylistHistory *history = m_player->history();
    if (history != 0) {

        prevPlaylistShortcut = new QShortcut(QKeySequence::Back, this);
        connect(prevPlaylistShortcut,   SIGNAL(activated()),    history, SLOT(prev()));

        nextPlaylistShortcut = new QShortcut(QKeySequence::Forward, this);
        connect(nextPlaylistShortcut,   SIGNAL(activated()),    history, SLOT(next()));
    }

    /* Other UI shortcuts */

//    findInPlaylist = new QShortcut(QKeySequence::Find, this);
//    connect(findInPlaylist,     SIGNAL(activated()),    this,               SLOT(toggleSearchVisibility()));

    showHistory = new QShortcut(Qt::CTRL + Qt::Key_H, this);
    connect(showHistory,        SIGNAL(activated()),    ui->actionHistory,  SLOT(toggle()));

//    focusOnPlaylist = new QShortcut(Qt::CTRL + Qt::Key_E, this);
//    connect(focusOnPlaylist,        SIGNAL(activated()),    ui->playlistView,   SLOT(setFocus()));

    focusOnFileFilter = new QShortcut(Qt::CTRL + Qt::Key_D, this);
    connect(focusOnFileFilter,  SIGNAL(activated()),    ui->fileWidget,     SLOT(setFocusOnFilter()));
}

void MainWindow::setConnections()
{
    connect(ui->buttonLoadFavorites,SIGNAL(clicked()),          this,               SLOT(loadFavorites()));

    connect(ui->buttonCopyPlaylist, SIGNAL(clicked()),          this,               SLOT(copyPlaylist()));

    connect(ui->actionAlways_on_top,SIGNAL(toggled(bool)),      this,               SLOT(toggleOnTop(bool)));
    connect(ui->actionAbout,        SIGNAL(triggered()),        this,               SLOT(showAboutDialog()));

    connect(ui->actionPlaylist,     SIGNAL(toggled(bool)),      ui->playlistWidget, SLOT(setVisible(bool)));
    connect(ui->actionFileSystem,   SIGNAL(toggled(bool)),      ui->fileWidget,     SLOT(setVisible(bool)));

    connect(ui->actionPlaylist,     SIGNAL(toggled(bool)),  this, SLOT(resizeToMinimumHeight()));
    connect(ui->actionFileSystem,   SIGNAL(toggled(bool)),  this, SLOT(resizeToMinimumHeight()));
    connect(ui->actionFlip,         SIGNAL(triggered()),    this, SLOT(flip()));
}

void MainWindow::initAudioUI()
{
    BASS::Core *audio = m_player->audio();
    if (audio == 0) return;

    ui->buttonPlayPause->setPlayer(audio);

    connect(ui->buttonLoop,     SIGNAL(toggled(bool)),      audio,              SLOT(setLoop(bool)));
    connect(audio,              SIGNAL(loopChanged(bool)),  ui->buttonLoop,     SLOT(setChecked(bool)));

    connect(ui->volumeWidget,   SIGNAL(volumeChanged(int)), audio,              SLOT(setVolume(int)));
    connect(audio,              SIGNAL(volumeChanged(int)), ui->volumeWidget,   SLOT(setVolume(int)));

    connect(ui->volumeWidget,   SIGNAL(muteToggled(bool)),  audio,              SLOT(setMute(bool)));
    connect(audio,              SIGNAL(muteToggled(bool)),  ui->volumeWidget,   SLOT(setMute(bool)));
}

void MainWindow::initCyclerUI()
{
    TrackCycler *cycler = m_player->cycler();
    if (cycler == 0) return;

    connect(cycler,             SIGNAL(trackChanged(PlayId,PlayId)),    this,       SLOT(setTitle(PlayId,PlayId)));

    connect(ui->buttonPrev,     SIGNAL(clicked()),              cycler,             SLOT(prev()));
    connect(ui->buttonNext,     SIGNAL(clicked()),              cycler,             SLOT(next()));

    connect(ui->buttonShuffle,  SIGNAL(toggled(bool)),          cycler,             SLOT(setShuffle(bool)));
    connect(cycler,             SIGNAL(shuffleChanged(bool)),   ui->buttonShuffle,  SLOT(setChecked(bool)));
}

void MainWindow::initOrientation()
{
    QActionGroup *orientationGroup = new QActionGroup(this);
    orientationGroup->addAction(ui->actionHorizontal);
    orientationGroup->addAction(ui->actionVertical);

    connect(orientationGroup, SIGNAL(triggered(QAction*)), this, SLOT(changeOrientation(QAction*)));
}

void MainWindow::toggleOnTop(bool checked)
{
    if (checked)
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    else
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);

    show();
}

void MainWindow::showAboutDialog()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::loadFavorites()
{
    const Playlist *favorites = Player::instance()->favorites()->playlist();
    if (favorites == 0 || favorites->isEmpty()) {
        QMessageBox::warning(this, "Error", "Favorites are empty! \n\nYou can add track to Favorites through the context menu of the track or by pushing the Star Button in the playlist.");
        return;
    }

    Playlist *playlist = new Playlist(favorites->urls());
    playlist->setName("Favorites");
    m_player->history()->replaceCurrent(playlist);
}

void MainWindow::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");

    settings.setValue("version",                QCoreApplication::applicationVersion());

    /* Widget visibility */

    settings.setValue("playlistWidget/visible", ui->playlistWidget->isVisibleTo(this));
    settings.setValue("fileWidget/visible",     ui->fileWidget->isVisibleTo(this));
    //settings.setValue("historyWidget/visible",  ui->historyWidget->isVisibleTo(this));

    /* Form geometry */

    settings.setValue("mainwindow/onTop",       ui->actionAlways_on_top->isChecked());
    settings.setValue("mainwindow/geometry",    saveGeometry());
    settings.setValue("splitter/geometry",      ui->splitter->saveState());
    settings.setValue("splitter/flip",          ui->splitter->widget(0) == ui->fileWidget);

    /* Widget stuff */

    settings.setValue("fileWidget/currentPath", ui->fileWidget->currentPath());

    /* Player */

    writePlayerSettings();
}

void MainWindow::writePlayerSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");

    /* Audio settings */

    BASS::Core *audio = m_player->audio();
    if (audio != 0) {
        settings.setValue("audio/volume",  audio->volume());
        settings.setValue("audio/mute",    audio->isMuted());
        settings.setValue("audio/loop",    audio->isLooped());
        //qDebug () << "audio/mute" << audio->isMuted();
    }

    /* Cycler settings */

    TrackCycler *cycler = m_player->cycler();
    if (cycler != 0) {
        settings.setValue("cycler/shuffle", cycler->shuffle());
        Playlist *playlist = cycler->playlist();
        if (playlist != 0)
            playlist->saveM3u(PlayerSettings::dataLocation()+"/current.m3u");
    }

    /* Favorites settings */

    FavoritesManager *favorites = m_player->favorites();
    if (favorites != 0) {
        favorites->playlist()->saveM3u(PlayerSettings::dataLocation()+"/favorites.m3u");
    }
}

void MainWindow::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");

    /* Widget visibility */

    bool fileWidgetVisible  = settings.value("fileWidget/visible").toBool();
    bool playlistVisible    = settings.value("playlistWidget/visible").toBool();
    bool historyVisible     = settings.value("historyWidget/visible").toBool();

    if (!settings.contains("fileWidget/visible"))
        fileWidgetVisible = true;
    if (!settings.contains("playlistWidget/visible"))
        playlistVisible = true;
    if (!settings.contains("historyWidget/visible"))
        historyVisible = false;

    ui->fileWidget->setVisible(fileWidgetVisible);
    ui->playlistWidget->setVisible(playlistVisible);
    //ui->historyWidget->setVisible(historyVisible);

    ui->actionFileSystem->setChecked(fileWidgetVisible);
    ui->actionPlaylist->setChecked(playlistVisible);
    ui->actionHistory->setChecked(historyVisible);

    // Always on top
    bool onTop = settings.value("mainwindow/onTop").toBool();
    ui->actionAlways_on_top->setChecked(onTop);
    toggleOnTop(onTop);

    // Mainwindow geometry
    if (ui->splitter->orientation() == Qt::Horizontal)
        ui->actionHorizontal->setChecked(true);
    if (ui->splitter->orientation() == Qt::Vertical)
        ui->actionVertical->setChecked(true);

    bool flipPerformed = settings.value("splitter/flip").toBool();
    if (flipPerformed)
        flip();

    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    ui->splitter->restoreState(settings.value("splitter/geometry").toByteArray());
    if (ui->splitter->orientation() == Qt::Vertical)
        ui->actionVertical->setChecked(true);
    else
        ui->actionHorizontal->setChecked(true);

//    ui->buttonLoop->setChecked(m_player->audio()->isLooped());
//    ui->buttonShuffle->setChecked(m_player->cycler()->shuffle());

    ui->fileWidget->cd(settings.value("fileWidget/currentPath").toString());

    readPlayerSettings();
}

void MainWindow::readPlayerSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");

    /* Audio settings */

    if (m_player->audio() != 0) {
        bool converted = false;
        int volume = settings.value("audio/volume").toInt(&converted);
        if (!converted)
            volume = 100;
        m_player->audio()->setVolume(volume);

        m_player->audio()->setMute(settings.value("audio/mute").toBool());
        m_player->audio()->setLoop(settings.value("audio/loop").toBool());
    }

    /* Cycler settings */

    if (m_player->cycler() != 0) {
        m_player->cycler()->setShuffle(settings.value("cycler/shuffle").toBool());

        Playlist *playlist = new Playlist(Playlist::fromM3u(PlayerSettings::dataLocation()+"/current.m3u"));
        playlist->setName("Last Session");
        m_player->history()->replaceCurrent(playlist);
    }

    /* Favorites settings */

    if (m_player->favorites() != 0) {
        QString fileName = PlayerSettings::dataLocation()+"/favorites.m3u";
        m_player->favorites()->setFavorites(Playlist::fromM3u(fileName));
    }
}

void MainWindow::copyPlaylist()
{
    Playlist *playlist = m_player->cycler()->playlist();

    if (playlist == 0 || playlist->isEmpty()) {
        QMessageBox::warning(this, "Error", "Playlist is empty. Nothing to copy!");
        return;
    }

    disableCopyPlaylist();

    DownloadPlaylistDialog *downloadDialog = new DownloadPlaylistDialog(playlist, this);
    connect(downloadDialog, SIGNAL(destroyed()), this, SLOT(enableCopyPlaylist()));
    downloadDialog->show();
}

void MainWindow::setTitle(PlayId prevId, PlayId curId)
{
    MediaLibrary *media = Player::instance()->media();
    if (media == 0) {
        setWindowTitle(curId.url().fileName());
        return;
    }

    MediaInfo *info = Player::instance()->media()->info(curId.url());

    QString artist = info->artist();
    QString title = info->title();

    if (info->isLocalFile() && artist.isEmpty() && title.isEmpty())
        setWindowTitle(info->fileName());
    else
        setWindowTitle(info->format("%artist – %title"));
}

void MainWindow::disableCopyPlaylist()
{
    ui->buttonCopyPlaylist->setEnabled(false);
}

void MainWindow::enableCopyPlaylist()
{
    ui->buttonCopyPlaylist->setEnabled(true);
}

void MainWindow::resizeToMinimumHeight()
{
//    qDebug() << ui->playlistWidget->isHidden();
//    qDebug() << ui->fileWidget->isHidden();
//    qDebug() << "---";

//    if (ui->fileWidget->isHidden() && ui->playlistWidget->isHidden()) {
//        m_lastGeometry = frameGeometry();
//        QRect newGeomerty = m_lastGeometry;
//        newGeomerty.setHeight(0);
//        setGeometry(newGeomerty);
//    }
//    else {
//        setGeometry(m_lastGeometry);
    //    }
}

void MainWindow::flip()
{
    ui->splitter->insertWidget(0, ui->splitter->widget(1));
}

void MainWindow::changeOrientation(QAction *action)
{
    if (action == ui->actionHorizontal)
        ui->splitter->setOrientation(Qt::Horizontal);

    if (action == ui->actionVertical)
        ui->splitter->setOrientation(Qt::Vertical);
}
