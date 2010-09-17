#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QSplitter>
#include <QFileDialog>
#include <QDesktopServices>

#include <okplayer.h>
#include <okWidgets/oktracktimelabel.h>

#include <aboutdialog.h>
#include <savedialog.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    okPlayer* player;
    QSplitter* splitter;
    QSplitter* splitter2;

    void createMenu();
	void createSplitters();
	void setConnections();

    //сохраняет настройки
    void saveSettings();
    //восстанавливает настройки
    void restoreSettings();

private slots:
    void toggleOnTop(bool state);
    void showAboutDialog();
    void openPlaylist();
    void savePlaylist();
    void loadFavorites();
	void loadPlaylist(QModelIndex i);
	void openHelp();
};

#endif // MAINWINDOW_H
