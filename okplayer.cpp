#include "okplayer.h"

okPlayer::okPlayer()
{
    db = new okPlayerDb;

    vlc = new okVLCWrapper;
    vlc->setDb(db);

    //устанавливаем фильтры для отображения файлов
    fileExt << "*.wav" << "*.mp3" << "*.ogg" << "*.wma" << "*.flac";
    hddThread = new okHddThread(fileExt);

    connect(hddThread, SIGNAL(finished()), this, SLOT(playlistFromThread()));
    //connect(hddThread, SIGNAL(statsUpdated(int,int,int,QString)), this, SLOT(updateStats(int,int,int,QString)));

    fsModel = new QFileSystemModel;
    fsModel->setRootPath("/");
    fsModel->setNameFilters(fileExt);
    //делаем так, чтоб лишние файлы не показывались в дереве
    fsModel->setNameFilterDisables(false);

    connect(vlc, SIGNAL(finished()), this, SLOT(nextAuto()));

    setInsertionState(Replace);
    setPlayingModeState(StopAfterPlaylist);
}

okPlayer::~okPlayer()
{
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
    if(vlc->isPlaying() || !vlc->isFileSet())
    {
        QList<QTableWidgetItem*> list = playlistWidget->selectedItems();
        int count = list.count();
        if(count>0)
        {
            int row=0;
            int col=0;
            for(int i=0; i<count; i++)
            {
                row = list.at(i)->row();
                col = list.at(i)->column();
                if(col==0)
                {
                    play(row);
                    return;
                }
            }
        }
    }
    vlc->play();
}

void okPlayer::play(int num)
{
    if(num<0 || num>=playlistWidget->rowCount()) return;
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

void okPlayer::toggleTableStarItem(QTableWidgetItem *item)
{
    if(item->column() == 0) return;
	okTableStarItem* item2;
	item2 = (okTableStarItem*) item;
	item2->toggle();

	playlistWidget->starTrack(item->row(), item2->isChecked());
}

int okPlayer::getVolume()
{
    return vlc->getVolume();
}

void okPlayer::matchTracks(QString query)
{
    if(query.length() == 0)
    {
        //восстанавливаем состояние виджета на основе плейлиста
        int count = playlistWidget->rowCount();
        for(int i=0; i<count; i++)
                playlistWidget->showRow(i);
        return;
    }
    //выбираем треки, которые подходят и прячем ряд, если трек не подходит
    int count = playlistWidget->rowCount();
    QString path;

    for(int i=0; i<count; i++)
    {
        path = playlistWidget->item(i, 0)->data(Qt::DisplayRole).toString();
        //если в имени файла есть запрашиваемая частица (подстрока)
        if(path.contains(query, Qt::CaseInsensitive))
            playlistWidget->showRow(i);
        else playlistWidget->hideRow(i);
    }
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
        //если это плейлист, который, кстати, не может попасть через дерево папок
        if(path.right(path.length() - path.lastIndexOf(".")).toLower() == ".m3u")
        {
            playlistFromFile(path);
            return;
        }

        QStringList src;
        src << path;
        playlistWidget->fillFromList(src, append);

        if(!append) play(0);
    }
}

void okPlayer::playlistFromThread()
{
    playlistWidget->fillFromList(hddThread->getPlaylist(), hddThread->getAppend());
    db->addTracks(hddThread->getPlaylist());

    if(insertionState == Replace) play(0);
}

void okPlayer::playlistFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Couldn't open file" << fileName;
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QStringList src;
    QString line;
    QString dir = QFileInfo(file).absoluteDir().path();
    while(!in.atEnd())
    {
        line = in.readLine();
        if(QFile::exists(line)) src << line;
        if(QFile::exists(dir+"/"+line)) src << dir+"/"+line;
    }
    file.close();
    playlistWidget->fillFromList(src);
}

void okPlayer::playlistToFile(const QStringList &playlist, const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString track;
    foreach(track, playlist)
    {
        out << track << "\n";
    }
    file.close();
}

void okPlayer::playlistToFile(const QString& fileName)
{
    playlistToFile(playlistWidget->getPlaylist(), fileName);
}

void okPlayer::playlistFromFavourites()
{
    playlistWidget->fillFromFavourites();
}

void okPlayer::newPlaylistFromIndex(QModelIndex i)
{
    newPlaylistFromIndex(i, false);
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
    playlistFromFile(fileName);
    play(0);
}

void okPlayer::newPlaylistFromPath(const QString &path)
{
    setInsertionState(Replace);
    playlistFromPath(path);

    QFileInfo fInfo(path);
    if(!fInfo.isDir()) play(0);
}

void okPlayer::addToPlaylistFromIndex(QModelIndex i)
{
    addToPlaylistFromIndex(i, false);
}

void okPlayer::addToPlaylistFromIndex(QModelIndex i, bool onlyRoot)
{
    setInsertionState(Append);
    playlistFromIndex(i, onlyRoot);
}

void okPlayer::addToPlaylistFromFile(const QString& fileName)
{
    setInsertionState(Append);
    playlistFromFile(fileName);
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

void okPlayer::writeFavouritesToFile()
{
    playlistToFile(playlistWidget->getFavouriteTracks(), QApplication::applicationDirPath()+"/favourites.m3u");
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
    playlistFromFile(fileName);
}

okVLCWrapper* okPlayer::getVLCWrapper()
{
    return vlc;
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
