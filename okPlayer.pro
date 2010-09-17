# -------------------------------------------------
# Project created by QtCreator 2010-06-19T19:18:50
# -------------------------------------------------
TARGET = okPlayer
TEMPLATE = app
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
    okWidgets/okdirtreeview.cpp \
    okWidgets/oklotsofstatesbutton.cpp \
    okWidgets/okplaylistlistwidget.cpp \
    savedialog.cpp
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
    okWidgets/okdirtreeview.h \
    okWidgets/oklotsofstatesbutton.h \
    okWidgets/okplaylistlistwidget.h \
    savedialog.h
FORMS += mainwindow.ui \
	aboutdialog.ui \
    savedialog.ui
RESOURCES += icons.qrc
LIBS += "G:/Documents/workspace/okPlayer/vlc/libvlc.dll" # if you are at windows os
