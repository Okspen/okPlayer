#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QSplitter>
#include <QShortcut>
#include <QFileDialog>
#include <QProgressDialog>
#include <QDesktopServices>

#include <okplayer.h>
#include <okWidgets/oktracktimelabel.h>

#include <aboutdialog.h>
#include <savedialog.h>
#include <dbbrowser.h>

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
    Ui::MainWindow *ui;
    okPlayer* player;
    QShortcut* findInPlaylist;
    QSplitter* dirPlaylistSplitter;

    void setConnections();

    //сохраняет настройки
    void saveSettings();
    //восстанавливает настройки
    void restoreSettings();

private slots:
    void toggleOnTop(bool state);
    void toggleSearchVisibility();
    void showAboutDialog();
    void openPlaylist();
    void savePlaylist();
    void copyPlaylist();
    void loadFavorites();
    void openHelp();
    void openMusicBrowser();
    void refreshFileSystem();
};

#endif // MAINWINDOW_H
