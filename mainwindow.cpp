#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	createSplitters();

    QStringList playingModes;
    playingModes << "Stop After Track" << "Stop After Playlist" << "Loop Track" << "Loop Playlist";
	ui->buttonPlayingModeState->setLabels(playingModes);
	ui->buttonPlayingModeState->setState(1);

    player = new okPlayer;

	player->setPlaylistWidget(ui->playlistWidget);
	player->setTreeWidget(ui->dirTree);
	player->setSeekSlider(ui->sliderSeek);

    ui->label->setVLC(player->getVLCWrapper());

	ui->playlistListWidget->setHidden(true);

	setConnections();

    restoreSettings();

	createMenu();
}

MainWindow::~MainWindow()
{
    saveSettings();
	ui->buttonMenu->actions().clear();
    delete ui;
    delete player;
}

void MainWindow::createSplitters()
{
	splitter = new QSplitter(Qt::Vertical, ui->centralWidget);
	splitter->addWidget(ui->playlistWidget);
	splitter->addWidget(ui->dirTree);
	ui->verticalLayout->addWidget(splitter);

	splitter2 = new QSplitter(Qt::Horizontal, ui->centralWidget);
	splitter2->addWidget(splitter);
	splitter2->addWidget(ui->playlistListWidget);
	ui->horizontalLayout_5->addWidget(splitter2);
}

void MainWindow::setConnections()
{
	connect(player, SIGNAL(statusChanged(QString)), ui->statusBar, SLOT(showMessage(QString)));

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

	connect(ui->fieldQuickSearch, SIGNAL(textChanged(QString)), player, SLOT(matchTracks(QString)));

	connect(ui->playlistWidget, SIGNAL(itemClicked(QTableWidgetItem*)), player, SLOT(toggleTableStarItem(QTableWidgetItem*)));
	connect(ui->playlistWidget, SIGNAL(droppedMediaToReplace(QString)), player, SLOT(newPlaylistFromPath(QString)));
	connect(ui->playlistWidget, SIGNAL(droppedMediaToAppend(QString)), player, SLOT(addToPlaylistFromPath(QString)));
	connect(ui->playlistWidget, SIGNAL(trackSelected(QString)), player, SLOT(play(QString)));

	connect(ui->buttonPlayingModeState, SIGNAL(stateChanged(int)), player, SLOT(setPlayingModeState(int)));

	//кнопки открытия и сохранения плейлистов
	connect(ui->buttonSavePlaylist, SIGNAL(clicked()), this, SLOT(savePlaylist()));
	connect(ui->buttonLoadFavorites, SIGNAL(clicked()), this, SLOT(loadFavorites()));

	connect(ui->playlistListWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(loadPlaylist(QModelIndex)));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::createMenu()
{
    QMenu* menu = new QMenu(this);

	QAction* actionView = new QAction("View", menu);
	menu->insertAction(0, actionView);
	QMenu* viewMenu = new QMenu(this);
	actionView->setMenu(viewMenu);

	QAction* actionViewPlaylist = new QAction("Playlist", viewMenu);
	actionViewPlaylist->setCheckable(true);
	actionViewPlaylist->setChecked(ui->playlistWidget->isVisibleTo(this));

	connect(actionViewPlaylist, SIGNAL(toggled(bool)), ui->playlistWidget, SLOT(setVisible(bool)));
	viewMenu->insertAction(0, actionViewPlaylist);

	QAction* actionViewDirectoryTree = new QAction("Directory tree", viewMenu);
	actionViewDirectoryTree->setCheckable(true);
	actionViewDirectoryTree->setChecked(ui->dirTree->isVisibleTo(this));
	connect(actionViewDirectoryTree, SIGNAL(toggled(bool)), ui->dirTree, SLOT(setVisible(bool)));
	viewMenu->insertAction(0, actionViewDirectoryTree);

	QAction* actionViewPlaylistManager = new QAction("Playlist manager", viewMenu);
	actionViewPlaylistManager->setCheckable(true);
	actionViewPlaylistManager->setChecked(ui->playlistListWidget->isVisibleTo(this));
	connect(actionViewPlaylistManager, SIGNAL(toggled(bool)), ui->playlistListWidget, SLOT(setVisible(bool)));
	viewMenu->insertAction(0, actionViewPlaylistManager);

	QAction* actionAlwaysOnTop = new QAction("Always On Top", menu);
	actionAlwaysOnTop->setCheckable(true);
	actionAlwaysOnTop->setChecked(false);
	actionAlwaysOnTop->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
	connect(actionAlwaysOnTop, SIGNAL(toggled(bool)), this, SLOT(toggleOnTop(bool)));
	menu->insertAction(0, actionAlwaysOnTop);

	QAction* actionHelp = new QAction("Help", menu);
	connect(actionHelp, SIGNAL(triggered()), this, SLOT(openHelp()));
	menu->insertAction(0, actionHelp);

	QAction* actionAbout = new QAction("About", menu);
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	menu->insertAction(0, actionAbout);

    ui->buttonMenu->setMenu(menu);
}

void MainWindow::toggleOnTop(bool checked)
{
    if(checked)
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    else
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();
}

void MainWindow::showAboutDialog()
{
	aboutDialog about(this);
    about.exec();
}

void MainWindow::saveSettings()
{
	player->playlistToFile("current.m3u");
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
	settings.setValue("playlistManager/visible", ui->playlistListWidget->isVisibleTo(this));

	settings.setValue("mainwindow/geometry", saveGeometry());
	settings.setValue("splitter/sizes", splitter->saveState());
	settings.setValue("splitterHorizontal/sizes", splitter2->saveState());
}

void MainWindow::restoreSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Okspen", "okPlayer");
    bool* ok = false;

    player->setVolume(settings.value("player/volume").toInt(ok));
    ui->sliderVolume->setValue(player->getVolume());

	ui->playlistWidget->setFavouritesFromFile("favourites.m3u");

    player->restorePlaylist(settings.value("player/playlist").toString());
	ui->playlistWidget->setSelected(settings.value("player/currentTrack").toInt());
    player->playCurrent();

    player->setPlayingModeState(settings.value("player/playingMode").toInt());
	ui->buttonPlayingModeState->setState(settings.value("player/playingMode").toInt());

	ui->dirTree->setCurrentIndex(player->getIndexFromPath(settings.value("dirTree/currentPath").toString()));
	ui->dirTree->setVisible(settings.value("dirTree/visible").toBool());

	ui->playlistWidget->setVisible(settings.value("playlist/visible").toBool());

	ui->playlistListWidget->setVisible(settings.value("playlistManager/visible").toBool());

	if(!settings.contains("dirTree/visible")) ui->dirTree->setVisible(true);
	if(!settings.contains("playlist/visible")) ui->playlistWidget->setVisible(true);
	if(!settings.contains("playlistManager/visible")) ui->playlistListWidget->setVisible(true);

	restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    splitter->restoreState(settings.value("splitter/sizes").toByteArray());
	splitter2->restoreState(settings.value("splitterHorizontal/sizes").toByteArray());
}

void MainWindow::openPlaylist()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Playlist"),
                                                    "", tr("Playlist (*.m3u)"));
    player->playlistFromFile(fileName);
}

void MainWindow::savePlaylist()
{
	savedialog dialog(this);
	if(dialog.exec()==1)
	{
		player->playlistToFile(dialog.fileName());
		ui->playlistListWidget->updateList();
	}
}

void MainWindow::loadFavorites()
{
    player->playlistFromFavourites();
}

void MainWindow::loadPlaylist(QModelIndex i)
{
	player->playlistFromFile(i.data(Qt::UserRole).toString());
}

void MainWindow::openHelp()
{
	QDesktopServices::openUrl("file:///" + QApplication::applicationDirPath() + "/help/index.html");
}
