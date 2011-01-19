#include "okplayer.h"

okPlayer::okPlayer()
{
    db = new okPlayerDb;

    vlc = new okVLCWrapper;
    vlc->setDb(db);

    //устанавливаем фильтры для отображения файлов
    fileExt << "*.wav" << "*.mp3" << "*.ogg" << "*.wma" << "*.flac" << "*.m4a";
    hddThread = new okHddThread(fileExt);

    connect(hddThread, SIGNAL(finished()), this, SLOT(playlistFromThread()));

    fsModel = new QFileSystemModel;
    fsModel->setRootPath("");
    fsModel->setNameFilters(fileExt);
    //делаем так, чтоб лишние файлы не показывались в дереве
    fsModel->setNameFilterDisables(false);

    connect(vlc, SIGNAL(finished()), this, SLOT(nextAuto()));

    setInsertionState(Replace);
    setPlayingModeState(StopAfterPlaylist);
}

okPlayer::~okPlayer()
{
    db->stop();
    delete db;
    delete vlc;
    delete hddThread;
    delete fsModel;
}

void okPlayer::setPlaylistWidget(okPlaylistWidget *list)
{
    if(list == 0) return;

    playlistWidget = list;
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->verticalHeader()->setVisible(false);
    playlistWidget->setColumnCount(2);
    playlistWidget->horizontalHeader()->setVisible(false);
    playlistWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    playlistWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
    playlistWidget->setColumnWidth(1, 24);
    playlistWidget->setSortingEnabled(true);
}

void okPlayer::setTreeWidget(QTreeView *tree)
{
    if(tree == 0) return;

    dirTree = tree;
    dirTree->setModel(fsModel);
    //убираем колонки с размером, типом и датой
    dirTree->setColumnHidden(1, true);
    dirTree->setColumnHidden(2, true);
    dirTree->setColumnHidden(3, true);
    //убираем заголовок
    dirTree->setHeaderHidden(true);
}

void okPlayer::setSeekSlider(okSeekSlider *slider)
{
    if(slider == 0) return;

    seekSlider = slider;
    seekSlider->setVLC(vlc);
}

void okPlayer::stop()
{
    vlc->stop();
}

void okPlayer::pause()
{
    vlc->pause();
}

void okPlayer::play()
{
    vlc->play();
}

void okPlayer::play(int num)
{
    if(num<0 || num>=playlistWidget->rowCount())
    {
        stop(); play();
        return;
    }
    play(playlistWidget->fileNameByRow(num));
    playlistWidget->setSelected(num);
}

void okPlayer::play(const QString& fileName)
{
    vlc->setFile(fileName);
    vlc->play();
}

void okPlayer::playRandom()
{
    int count = playlistWidget->rowCount();
    if(count == 0) return;
    play(qrand() % count);
}

void okPlayer::playCurrent()
{
    play();
}

void okPlayer::prev()
{
    int index = playlistWidget->getSelected() - 1;
    if(index < 0)
        index = playlistWidget->rowCount() - 1;

    play(index);
}

void okPlayer::next()
{
    int index = playlistWidget->getSelected() + 1;
    //если мы дошли до конца плейлиста и нужно начать сначала
    if(index >= playlistWidget->rowCount())
        index = 0;
    play(index);
}

void okPlayer::nextAuto()
{
    int currentTrack = playlistWidget->getSelected();

    switch(playingModeState)
    {
        case StopAfterTrack:
            return;
        break;

        case StopAfterPlaylist:
            if(currentTrack == playlistWidget->rowCount()-1) return;
            next();
        break;

        case LoopTrack:
            stop();
            play();
        break;

        case LoopPlaylist:
            next();
        break;

        case RandomTrack:
            playRandom();
        break;
    }
}

void  okPlayer::setVolume(int v)
{
    vlc->setVolume(v);
}

QStringList okPlayer::getFileExt()
{
    return fileExt;
}

void okPlayer::setPlayingModeState(int newState)
{
    //playingModeState = newState;
    switch(newState)
    {
    case 0: setPlayingModeState(LoopTrack);
        break;
    case 1: setPlayingModeState(LoopPlaylist);
        break;
    case 2: setPlayingModeState(StopAfterTrack);
        break;
    case 3: setPlayingModeState(StopAfterPlaylist);
        break;
    case 4: setPlayingModeState(RandomTrack);
    }
}

int okPlayer::getVolume()
{
    return vlc->getVolume();
}

void okPlayer::playlistFromIndex(QModelIndex i, bool onlyRoot)
{
    playlistFromPath(fsModel->filePath(i), onlyRoot);
}

void okPlayer::playlistFromPath(const QString& path, bool onlyRoot)
{
    QFileInfo fInfo;
    fInfo.setFile(path);

    bool append = false;
    if(insertionState == Append) append = true;

    if(fInfo.isDir())
    {
        hddThread->setPath(path);
        hddThread->setAppend(append);
        hddThread->setOnlyRoot(onlyRoot);
        hddThread->start();
        hddThread->setPriority(QThread::LowPriority);
    }
    else
    {
        QString extension = path.right(path.length() - path.lastIndexOf(".")).toLower();
        //если это плейлист, который, кстати, не может попасть через дерево папок
        if(extension == ".m3u")
        {
            playlistWidget->replace(new okPlaylist(path));
            return;
        }
        else if(!fileExt.contains("*"+extension))
        {
            qDebug() << "unsupported file type";
            return;
        }

        QStringList src;
        src << path;
        if(append) playlistWidget->append(src);
        else
        {
            playlistWidget->replace(src);
            play(0);
        }
    }
}

void okPlayer::playlistFromThread()
{
    okPlaylist* list = hddThread->getPlaylist();

    db->addTracks(list);
    if(hddThread->getAppend())
        playlistWidget->append(list);
    else
    {
        playlistWidget->replace(list);
        play(0);
    }
}

void okPlayer::newPlaylistFromIndex(QModelIndex i, bool onlyRoot)
{
    setInsertionState(Replace);
    playlistFromIndex(i, onlyRoot);
    if(!fsModel->isDir(i)) play(0);
}

void okPlayer::newPlaylistFromFile(const QString& fileName)
{
    setInsertionState(Replace);
    playlistWidget->replace(new okPlaylist(fileName));
    play(0);
}

void okPlayer::newPlaylistFromPath(const QString &path)
{
    setInsertionState(Replace);
    playlistFromPath(path);

    QFileInfo fInfo(path);
    if(!fInfo.isDir()) play(0);
}

void okPlayer::addToPlaylistFromIndex(QModelIndex i, bool onlyRoot)
{
    setInsertionState(Append);
    playlistFromIndex(i, onlyRoot);
}

void okPlayer::addToPlaylistFromFile(const QString& fileName)
{
    playlistWidget->append(new okPlaylist(fileName));
}

void okPlayer::addToPlaylistFromThread()
{
    setInsertionState(Append);
    playlistFromThread();
}

void okPlayer::addToPlaylistFromPath(const QString& path)
{
    setInsertionState(Append);
    playlistFromPath(path);
}

void okPlayer::setInsertionState(InsertionMode newMode)
{
    insertionState = newMode;
}

void okPlayer::setPlayingModeState(PlayingMode newMode)
{
    playingModeState = newMode;
}

void okPlayer::writeCurrentPlaylistToFile()
{
    QString path = QApplication::applicationDirPath()+"/current.m3u";
    playlistWidget->getPlaylist()->writeToFile(path);
}

void okPlayer::writeFavouritesToFile()
{
    QString path = QApplication::applicationDirPath()+"/favourites.m3u";
    playlistWidget->getFavouriteTracks()->writeToFile(path);
}

void okPlayer::restorePlaylist(const QString &fileName)
{
    QStringList arguments = QCoreApplication::arguments();
    int argCount = arguments.count();

    if(argCount > 1)
    {
        setInsertionState(Replace);
        playlistFromPath(arguments.at(1));

        if(argCount > 2)
        {
            setInsertionState(Append);
            for(int i=2; i<argCount; i++)
                playlistFromPath(arguments.at(i));
        }
        return;
    }
    playlistWidget->replace(new okPlaylist(fileName));
}

QString okPlayer::getFSPath()
{
    return fsModel->filePath(dirTree->currentIndex());
}

QModelIndex okPlayer::getIndexFromPath(const QString& path)
{
    return fsModel->index(path);
}

int okPlayer::getPlayingMode()
{
    return playingModeState;
}

okPlayerDb* okPlayer::getDb()
{
    return db;
}
