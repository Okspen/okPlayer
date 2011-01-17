#ifndef OKPLAYER_H
#define OKPLAYER_H

#include <QApplication>
#include <QToolButton>
#include <QTableWidget>
#include <QTreeView>
#include <QHeaderView>
#include <QObject>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QSettings>
#include <QLayout>

#include <okplayerdb.h>
#include <okvlcwrapper.h>

#include <okhddthread.h>
#include <okWidgets/okseekslider.h>
#include <okWidgets/oktablestaritem.h>
#include <okWidgets/okplaylistwidget.h>

using namespace std;

class okPlayer : public QObject
{
    Q_OBJECT
public:
    /*
        как добавлять новые элементы в плейлист:
        Append - добавлять в конец
        Replace - заменять на новые
    */
    enum InsertionMode {Append, Replace};
    enum PlayingMode {LoopTrack = 0,
                      LoopPlaylist = 1,
                      StopAfterTrack = 2,
                      StopAfterPlaylist = 3,
                      RandomTrack = 4
                    };

    okPlayer();
    ~okPlayer();
    //аксесоры для объектов интерфейса
    void setPlaylistWidget(okPlaylistWidget* list);
    void setTreeWidget(QTreeView* tree);
    void setSeekSlider(okSeekSlider* slider);

    //возвращает уровень звука от 0 до 100
    int getVolume();

    //возвращает список расширений файлов, которые можно добавлять при сканировании
    QStringList getFileExt();
    //возвращает указатель на объект обертки VLC
    okVLCWrapper* getVLCWrapper();

    //возвращает текущий открытый путь в окне dirTree
    QString getFSPath();
    QModelIndex getIndexFromPath(const QString& path);

    int getCurrentTrack();
    int getPlayingMode();

    okPlayerDb* getDb();

    //загружает список любимых треков из файла в память
    void setFavouritesFromFile();
    //восстанавливает плейлист после запуска приложения. если приложение запущено с параметрами, то плейлист строится по ним.
    void restorePlaylist(const QString& fileName);

private:
    okPlayerDb* db;
    okVLCWrapper* vlc;
    okHddThread* hddThread;

    //список расширений файлов, которые можно добавлять при сканировании
    QStringList fileExt;

    /* указатели на объекты интерфейса */

    //плейлист
    okPlaylistWidget* playlistWidget;
    //дерево папок
    QTreeView* dirTree;
    //слайдер поиска по треку
    okSeekSlider* seekSlider;

    //модель файловой системы для дерева папок
    QFileSystemModel* fsModel;

    InsertionMode insertionState;
    PlayingMode playingModeState;

    void setInsertionState(InsertionMode newMode);
    void setPlayingModeState(PlayingMode newMode);

    /* методы задания плейлиста */

    //плейлист создается на основе элемента дерева (QModelIndex i) по которому кликнули
    void playlistFromIndex(QModelIndex i, bool onlyRoot);

    void playlistFromPath(const QString& path, bool onlyRoot=false);

public slots:
    //задает уровень звука, принимает значения от 0 до 100
    void setVolume(int v);
    //проигрывание останавливается и seekbar устанавливается в начало
    void stop();
    //проигрывание ставится на паузу
    void pause();
    //начинает играть текущий файл.
    void play();
    //начинает играть файл под номером num в плейлисте
    void play(int num);
    //начинает играть файл по адресу
    void play(const QString& fileName);
    //начинает играть случайный файл из плейлиста
    void playRandom();
    //начнет играть текущий файл
    void playCurrent();
    // начинает играть предыдущий файл
    void prev();
    //начинает играть следующий файл
    void next();
    //проигрывает следующий трек относительно loopMode и stopMode
    //auto потому, что вызывается, когда проигрывание трека подошло к концу
    void nextAuto();

    /* обертки для методов создания плейлистов */

    //создается новый плейлист
    void newPlaylistFromIndex(QModelIndex i, bool onlyRoot=false);
    void newPlaylistFromFile(const QString& fileName);
    void newPlaylistFromPath(const QString& path);

    //добавляется к текущему
    void addToPlaylistFromIndex(QModelIndex i, bool onlyRoot=false);
    void addToPlaylistFromThread();
    void addToPlaylistFromFile(const QString& fileName);
    void addToPlaylistFromPath(const QString& path);

    //плейлист берется из треда
    void playlistFromThread();

    void setPlayingModeState(int newState);

    //записывает сохраняет плейлисты в файл
    void writeCurrentPlaylistToFile();
    void writeFavouritesToFile();
};

#endif // OKPLAYER_H
