# -------------------------------------------------
# Project created by QtCreator 2010-06-19T19:18:50
# -------------------------------------------------
TARGET = okPlayer
TEMPLATE = app
CONFIG  += qaxcontainer
QT += sql
INCLUDEPATH += G:\Documents\workspace\okPlayer\taglib
INCLUDEPATH += G:\Documents\workspace\okPlayer\taglib\toolkit
SOURCES += main.cpp \
    mainwindow.cpp \
    okplayer.cpp \
    okhddthread.cpp \
    okvlcwrapper.cpp \
    aboutdialog.cpp \
    okWidgets/oktracktimelabel.cpp \
    okWidgets/oktablestaritem.cpp \
    okWidgets/okseekslider.cpp \
    okWidgets/okplaylistwidget.cpp \
    okWidgets/okplaypausebutton.cpp \
    okWidgets/okdirtreeview.cpp \
    savedialog.cpp \
    okplayerdb.cpp \
    dbbrowser.cpp \
    statsdialog.cpp \
    okplaylist.cpp
HEADERS += mainwindow.h \
    okplayer.h \
    okhddthread.h \
    vlc/vlc.h \
    okvlcwrapper.h \
    aboutdialog.h \
    okWidgets/oktracktimelabel.h \
    okWidgets/oktablestaritem.h \
    okWidgets/okseekslider.h \
    okWidgets/okplaylistwidget.h \
    okWidgets/okplaypausebutton.h \
    okWidgets/okdirtreeview.h \
    savedialog.h \
    okplayerdb.h \
    dbbrowser.h \
    statsdialog.h \
    okplaylist.h
FORMS += mainwindow.ui \
	aboutdialog.ui \
    savedialog.ui \
    dbbrowser.ui \
    statsdialog.ui
RESOURCES += icons.qrc
LIBS += "G:/Program Files/VLC/libvlc.dll" # if you are at windows os
#LIBS += "C:/Program Files/okPlayer/libvlc.dll" # if you are at windows os
LIBS += "G:\Documents\workspace\okPlayer-build-desktop\debug\taglib.dll" # if you are at windows os
