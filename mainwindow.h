#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QShortcut>
#include <QActionGroup>

#include "aboutdialog.h"
#include "downloadplaylistdialog.h"

#include "widgets/playlist/playlistview.h"

#include "player/playersettings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *event);

private:
    Ui::MainWindow  *ui;
    Player          *m_player;

    QShortcut       *findInPlaylist;
    QShortcut       *showHistory;
    QShortcut       *focusOnPlaylist;
    QShortcut       *focusOnFileFilter;
    QShortcut       *nextShortcut;
    QShortcut       *previousShortcut;
    QShortcut       *volumeUpShortcut;
    QShortcut       *volumeDownShortcut;
    QShortcut       *playShortcut;
    QShortcut       *playPauseShortcut;
    QShortcut       *pauseShortcut;
    QShortcut       *prevPlaylistShortcut;
    QShortcut       *nextPlaylistShortcut;

    QStringList     m_nameFilters;

    void createShortcuts();
    void setConnections();

    void initAudioUI();
    void initCyclerUI();
    void initOrientation();

    void writePlayerSettings();
    void readSettings();
    void readPlayerSettings();

private slots:
    void writeSettings();

    void toggleOnTop(bool state);

    void showAboutDialog();
    void loadFavorites();
    void copyPlaylist();
    void setTitle(PlayId prevId, PlayId curId);

    void disableCopyPlaylist();
    void enableCopyPlaylist();

    void resizeToMinimumHeight();
    void flip();
    void changeOrientation(QAction *action);
};

#endif // MAINWINDOW_H
