/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 15. Sep 18:10:07 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
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
#include "okWidgets/oklotsofstatesbutton.h"
#include "okWidgets/okplaylistlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonMenu;
    QToolButton *buttonStop;
    QToolButton *buttonPause;
    QToolButton *buttonPlay;
    QToolButton *buttonPrev;
    QToolButton *buttonNext;
    QToolButton *buttonRandom;
    QSlider *sliderVolume;
    QHBoxLayout *horizontalLayout_3;
    okLotsOfStatesButton *buttonPlayingModeState;
    okTrackTimeLabel *label;
    okSeekSlider *sliderSeek;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonSavePlaylist;
    QPushButton *buttonLoadFavorites;
    QLineEdit *fieldQuickSearch;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    okPlaylistListWidget *playlistListWidget;
    okPlaylistWidget *playlistWidget;
    okDirTreeView *dirTree;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(418, 494);
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
        buttonMenu = new QPushButton(centralWidget);
        buttonMenu->setObjectName(QString::fromUtf8("buttonMenu"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonMenu->sizePolicy().hasHeightForWidth());
        buttonMenu->setSizePolicy(sizePolicy);
        buttonMenu->setMinimumSize(QSize(50, 0));
        buttonMenu->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(buttonMenu);

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
        buttonPlayingModeState = new okLotsOfStatesButton(centralWidget);
        buttonPlayingModeState->setObjectName(QString::fromUtf8("buttonPlayingModeState"));

        horizontalLayout_3->addWidget(buttonPlayingModeState);

        label = new okTrackTimeLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
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
        buttonSavePlaylist = new QPushButton(centralWidget);
        buttonSavePlaylist->setObjectName(QString::fromUtf8("buttonSavePlaylist"));

        horizontalLayout_2->addWidget(buttonSavePlaylist);

        buttonLoadFavorites = new QPushButton(centralWidget);
        buttonLoadFavorites->setObjectName(QString::fromUtf8("buttonLoadFavorites"));

        horizontalLayout_2->addWidget(buttonLoadFavorites);

        fieldQuickSearch = new QLineEdit(centralWidget);
        fieldQuickSearch->setObjectName(QString::fromUtf8("fieldQuickSearch"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(fieldQuickSearch->sizePolicy().hasHeightForWidth());
        fieldQuickSearch->setSizePolicy(sizePolicy2);
        fieldQuickSearch->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(fieldQuickSearch);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_5->addLayout(verticalLayout);

        playlistListWidget = new okPlaylistListWidget(centralWidget);
        playlistListWidget->setObjectName(QString::fromUtf8("playlistListWidget"));

        horizontalLayout_5->addWidget(playlistListWidget);


        verticalLayout_2->addLayout(horizontalLayout_5);

        playlistWidget = new okPlaylistWidget(centralWidget);
        playlistWidget->setObjectName(QString::fromUtf8("playlistWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(playlistWidget->sizePolicy().hasHeightForWidth());
        playlistWidget->setSizePolicy(sizePolicy3);
        playlistWidget->setMinimumSize(QSize(0, 0));
        playlistWidget->setSizeIncrement(QSize(0, 0));
        playlistWidget->setAcceptDrops(true);
        playlistWidget->setFrameShape(QFrame::StyledPanel);
        playlistWidget->setFrameShadow(QFrame::Sunken);

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

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "okPlayer", 0, QApplication::UnicodeUTF8));
        buttonMenu->setText(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
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
        buttonPlayingModeState->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        buttonSavePlaylist->setText(QApplication::translate("MainWindow", "Save playlist", 0, QApplication::UnicodeUTF8));
        buttonLoadFavorites->setText(QApplication::translate("MainWindow", "Load favourites", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
