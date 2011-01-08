/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 7. Jan 14:35:00 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <okWidgets/okplaylistwidget.h>
#include <okWidgets/okseekslider.h>
#include <okWidgets/oktracktimelabel.h>
#include "okWidgets/okdirtreeview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAlways_on_top;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionMusic_browser;
    QAction *actionPlaylist;
    QAction *actionDirectory_tree;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonStop;
    QToolButton *buttonPause;
    QToolButton *buttonPlay;
    QToolButton *buttonPrev;
    QToolButton *buttonNext;
    QToolButton *buttonRandom;
    QSlider *sliderVolume;
    QHBoxLayout *horizontalLayout_3;
    okTrackTimeLabel *label;
    okSeekSlider *sliderSeek;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonCopyPlaylist;
    QComboBox *playModeBox;
    QPushButton *buttonLoadFavorites;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *fieldQuickSearch;
    QPushButton *pushButton;
    QVBoxLayout *splitterLayout;
    okPlaylistWidget *playlistWidget;
    okDirTreeView *dirTree;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuView_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(418, 494);
        actionAlways_on_top = new QAction(MainWindow);
        actionAlways_on_top->setObjectName(QString::fromUtf8("actionAlways_on_top"));
        actionAlways_on_top->setCheckable(true);
        actionAlways_on_top->setShortcutContext(Qt::ApplicationShortcut);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionMusic_browser = new QAction(MainWindow);
        actionMusic_browser->setObjectName(QString::fromUtf8("actionMusic_browser"));
        actionMusic_browser->setEnabled(false);
        actionPlaylist = new QAction(MainWindow);
        actionPlaylist->setObjectName(QString::fromUtf8("actionPlaylist"));
        actionPlaylist->setCheckable(true);
        actionDirectory_tree = new QAction(MainWindow);
        actionDirectory_tree->setObjectName(QString::fromUtf8("actionDirectory_tree"));
        actionDirectory_tree->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        buttonStop = new QToolButton(centralWidget);
        buttonStop->setObjectName(QString::fromUtf8("buttonStop"));
        buttonStop->setMinimumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tango/images/icons/tango/media-playback-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStop->setIcon(icon);
        buttonStop->setPopupMode(QToolButton::DelayedPopup);
        buttonStop->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonStop->setAutoRaise(true);
        buttonStop->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(buttonStop);

        buttonPause = new QToolButton(centralWidget);
        buttonPause->setObjectName(QString::fromUtf8("buttonPause"));
        buttonPause->setMinimumSize(QSize(24, 24));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/tango/images/icons/tango/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPause->setIcon(icon1);
        buttonPause->setAutoRaise(true);

        horizontalLayout->addWidget(buttonPause);

        buttonPlay = new QToolButton(centralWidget);
        buttonPlay->setObjectName(QString::fromUtf8("buttonPlay"));
        buttonPlay->setMinimumSize(QSize(24, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/tango/images/icons/tango/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPlay->setIcon(icon2);
        buttonPlay->setAutoRaise(true);

        horizontalLayout->addWidget(buttonPlay);

        buttonPrev = new QToolButton(centralWidget);
        buttonPrev->setObjectName(QString::fromUtf8("buttonPrev"));
        buttonPrev->setMinimumSize(QSize(24, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/tango/images/icons/tango/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPrev->setIcon(icon3);
        buttonPrev->setAutoRaise(true);

        horizontalLayout->addWidget(buttonPrev);

        buttonNext = new QToolButton(centralWidget);
        buttonNext->setObjectName(QString::fromUtf8("buttonNext"));
        buttonNext->setMinimumSize(QSize(24, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/tango/images/icons/tango/media-skip-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonNext->setIcon(icon4);
        buttonNext->setAutoRaise(true);

        horizontalLayout->addWidget(buttonNext);

        buttonRandom = new QToolButton(centralWidget);
        buttonRandom->setObjectName(QString::fromUtf8("buttonRandom"));
        buttonRandom->setMinimumSize(QSize(24, 24));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/tango/images/icons/tango/dialog-information.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonRandom->setIcon(icon5);
        buttonRandom->setAutoRaise(true);

        horizontalLayout->addWidget(buttonRandom);

        sliderVolume = new QSlider(centralWidget);
        sliderVolume->setObjectName(QString::fromUtf8("sliderVolume"));
        sliderVolume->setMaximum(100);
        sliderVolume->setValue(50);
        sliderVolume->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sliderVolume);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new okTrackTimeLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 21));
        label->setMaximumSize(QSize(16777215, 21));

        horizontalLayout_3->addWidget(label);

        sliderSeek = new okSeekSlider(centralWidget);
        sliderSeek->setObjectName(QString::fromUtf8("sliderSeek"));
        sliderSeek->setMinimumSize(QSize(0, 21));
        sliderSeek->setMaximumSize(QSize(16777215, 16777215));
        sliderSeek->setMaximum(1000);
        sliderSeek->setSingleStep(1);
        sliderSeek->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(sliderSeek);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        buttonCopyPlaylist = new QPushButton(centralWidget);
        buttonCopyPlaylist->setObjectName(QString::fromUtf8("buttonCopyPlaylist"));

        horizontalLayout_2->addWidget(buttonCopyPlaylist);

        playModeBox = new QComboBox(centralWidget);
        playModeBox->setObjectName(QString::fromUtf8("playModeBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playModeBox->sizePolicy().hasHeightForWidth());
        playModeBox->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(playModeBox);

        buttonLoadFavorites = new QPushButton(centralWidget);
        buttonLoadFavorites->setObjectName(QString::fromUtf8("buttonLoadFavorites"));

        horizontalLayout_2->addWidget(buttonLoadFavorites);


        verticalLayout_2->addLayout(horizontalLayout_2);

        searchWidget = new QWidget(centralWidget);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_4 = new QHBoxLayout(searchWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(searchWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        fieldQuickSearch = new QLineEdit(searchWidget);
        fieldQuickSearch->setObjectName(QString::fromUtf8("fieldQuickSearch"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fieldQuickSearch->sizePolicy().hasHeightForWidth());
        fieldQuickSearch->setSizePolicy(sizePolicy3);
        fieldQuickSearch->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(fieldQuickSearch);

        pushButton = new QPushButton(searchWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_2->addWidget(searchWidget);

        splitterLayout = new QVBoxLayout();
        splitterLayout->setSpacing(6);
        splitterLayout->setObjectName(QString::fromUtf8("splitterLayout"));

        verticalLayout_2->addLayout(splitterLayout);

        playlistWidget = new okPlaylistWidget(centralWidget);
        playlistWidget->setObjectName(QString::fromUtf8("playlistWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(playlistWidget->sizePolicy().hasHeightForWidth());
        playlistWidget->setSizePolicy(sizePolicy5);
        playlistWidget->setMinimumSize(QSize(0, 0));
        playlistWidget->setSizeIncrement(QSize(0, 0));
        playlistWidget->setAcceptDrops(true);
        playlistWidget->setFrameShape(QFrame::StyledPanel);
        playlistWidget->setFrameShadow(QFrame::Sunken);
        playlistWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        playlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        playlistWidget->horizontalHeader()->setVisible(false);
        playlistWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(playlistWidget);

        dirTree = new okDirTreeView(centralWidget);
        dirTree->setObjectName(QString::fromUtf8("dirTree"));
        dirTree->setFrameShape(QFrame::StyledPanel);
        dirTree->setRootIsDecorated(true);
        dirTree->header()->setVisible(false);
        dirTree->header()->setCascadingSectionResizes(false);
        dirTree->header()->setHighlightSections(false);
        dirTree->header()->setMinimumSectionSize(25);
        dirTree->header()->setStretchLastSection(true);

        verticalLayout_2->addWidget(dirTree);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 418, 26));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuView_2 = new QMenu(menuBar);
        menuView_2->setObjectName(QString::fromUtf8("menuView_2"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuView_2->menuAction());
        menuMenu->addAction(actionAlways_on_top);
        menuMenu->addAction(actionMusic_browser);
        menuMenu->addAction(actionHelp);
        menuMenu->addAction(actionAbout);
        menuView_2->addAction(actionPlaylist);
        menuView_2->addAction(actionDirectory_tree);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), fieldQuickSearch, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "okPlayer", 0, QApplication::UnicodeUTF8));
        actionAlways_on_top->setText(QApplication::translate("MainWindow", "Always on top", 0, QApplication::UnicodeUTF8));
        actionAlways_on_top->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionMusic_browser->setText(QApplication::translate("MainWindow", "Music browser", 0, QApplication::UnicodeUTF8));
        actionPlaylist->setText(QApplication::translate("MainWindow", "Playlist", 0, QApplication::UnicodeUTF8));
        actionDirectory_tree->setText(QApplication::translate("MainWindow", "Directory tree", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonStop->setToolTip(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonPause->setToolTip(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonPause->setText(QApplication::translate("MainWindow", "||", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonPlay->setToolTip(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonPlay->setText(QApplication::translate("MainWindow", ">", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonPrev->setToolTip(QApplication::translate("MainWindow", "Previous", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonPrev->setText(QApplication::translate("MainWindow", "|<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonNext->setToolTip(QApplication::translate("MainWindow", "Next", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonNext->setText(QApplication::translate("MainWindow", ">|", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonRandom->setToolTip(QApplication::translate("MainWindow", "Random", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonRandom->setText(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        buttonCopyPlaylist->setText(QApplication::translate("MainWindow", "Copy playlist", 0, QApplication::UnicodeUTF8));
        playModeBox->clear();
        playModeBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Loop track", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Loop playlist", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Stop after track", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Stop after playlist", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Random", 0, QApplication::UnicodeUTF8)
        );
        buttonLoadFavorites->setText(QApplication::translate("MainWindow", "Load favourites", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Find in playlist:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        menuView_2->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
