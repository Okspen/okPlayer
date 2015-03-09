# -------------------------------------------------
# Project created by QtCreator 2010-06-19T19:18:50
# -------------------------------------------------
TARGET = okPlayer

TEMPLATE = app
VERSION = 0.3.2.0
QMAKE_TARGET_COMPANY = Okspen Digital Solutions
QMAKE_TARGET_DESCRIPTION = "A simple but powerful audio player"
win32:RC_ICONS += images/icons/okplayer.ico

QT += widgets

INCLUDEPATH += include "." "include/bass/c" "include/tags/c"

DEFINES += NOMINMAX

SOURCES += main.cpp \
    aboutdialog.cpp \
    widgets/playlist/mediadroppeddialog.cpp \
    downloadplaylistdialog.cpp \
    mainwindow.cpp \
    widgets/volume/volumewidget.cpp \
    widgets/volume/volumebutton.cpp \
    widgets/playlist/playlistmodel.cpp \
    widgets/playlist/trackdelegate.cpp \
    widgets/playlist/playlistview.cpp \
    player/playlist.cpp \
    filecopythread.cpp \
    player/player.cpp \
    player/trackcycler.cpp \
    player/folderscanner.cpp \
    player/folderplayer.cpp \
    player/playersettings.cpp \
    player/playlisthistory.cpp \
    player/favoritesmanager.cpp \
    widgets/fastslider.cpp \
    player/playid.cpp \
    player/medialibrary.cpp \
    player/mediainfo.cpp \
    widgets/fs/filesystemview.cpp \
    widgets/fs/filesystemmodel.cpp \
    player/tagreader.cpp \
    player/bass/stream.cpp \
    widgets/tracktimelabel.cpp \
    widgets/playpausebutton.cpp \
    widgets/seekslider.cpp \
    player/bass/localstream.cpp \
    player/bass/core.cpp \
    widgets/search/searchwidget.cpp \
    widgets/fs/filesystemwidget.cpp \
    widgets/fs/filesystemitemdelegate.cpp \
    widgets/fs/scanprogressdialog.cpp \
    widgets/playlist/playlistwidget.cpp \
    widgets/history/historymodel.cpp \
    widgets/history/historywidget.cpp \
    widgets/playlist/favoritesfiltermodel.cpp \
    player/playorder.cpp \
    widgets/playlist/playcountdialog.cpp

HEADERS += mainwindow.h \
    aboutdialog.h \
    widgets/volume/volumewidget.h \
    widgets/volume/volumebutton.h \
    player/trackcycler.h \
    player/playlist.h \
    widgets/playlist/mediadroppeddialog.h \
    widgets/playlist/playlistmodel.h \
    filecopythread.h \
    downloadplaylistdialog.h \
    widgets/playlist/trackdelegate.h \
    widgets/playlist/playlistview.h \
    player/player.h \
    player/folderscanner.h \
    player/folderplayer.h \
    player/playersettings.h \
    player/playlisthistory.h \
    player/favoritesmanager.h \
    widgets/fastslider.h \
    player/playid.h \
    player/medialibrary.h \
    player/mediainfo.h \
    widgets/fs/filesystemview.h \
    widgets/fs/filesystemmodel.h \
    player/tagreader.h \
    player/bass/stream.h \
    widgets/tracktimelabel.h \
    widgets/playpausebutton.h \
    widgets/seekslider.h \
    player/bass/localstream.h \
    player/bass/core.h \
    widgets/search/searchwidget.h \
    widgets/fs/filesystemwidget.h \
    widgets/fs/filesystemitemdelegate.h \
    widgets/fs/scanprogressdialog.h \
    widgets/playlist/playlistwidget.h \
    widgets/history/historymodel.h \
    widgets/history/historywidget.h \
    widgets/playlist/favoritesfiltermodel.h \
    player/playorder.h \
    widgets/playlist/playcountdialog.h

FORMS += mainwindow.ui \
    aboutdialog.ui \
    widgets/playlist/mediadroppeddialog.ui \
    downloadplaylistdialog.ui \
    widgets/volume/volumewidget.ui \
    widgets/search/searchwidget.ui \
    widgets/fs/filesystemwidget.ui \
    widgets/fs/scanprogressdialog.ui \
    widgets/playlist/playlistwidget.ui \
    widgets/history/historywidget.ui \
    widgets/playlist/playcountdialog.ui

RESOURCES += icons.qrc

win32 {
    LIBS += "../lib/bass.lib"
    LIBS += "../lib/tags.lib"
}
