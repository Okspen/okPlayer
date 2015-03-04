#include "historywidget.h"
#include "ui_historywidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    m_model = new HistoryModel(this);
    ui->playlistCombo->setModel(m_model);
    ui->playlistCombo->view()->setTextElideMode(Qt::ElideRight);

    m_history = Player::instance()->history();
    setEnabled((m_history->playlists() != 0) && (m_history->playlists()->count() != 0));

    connect(m_history,          SIGNAL(currentChanged(Playlist*)),  this,       SLOT(onPlaylistChanged(Playlist *)));
    connect(ui->playlistCombo,  SIGNAL(currentIndexChanged(int)),   m_history,  SLOT(switchPlaylist(int)));

    connect(ui->playlistCombo,  SIGNAL(currentIndexChanged(int)),   this,       SLOT(onCurrentIndexChanged(int)));

    connect(m_history,  SIGNAL(countChanged()), this, SLOT(onCountChanged()));

    connect(ui->prevButton,     SIGNAL(clicked()), m_history, SLOT(prev()));
    connect(ui->nextButton,     SIGNAL(clicked()), m_history, SLOT(next()));
    connect(ui->deleteButton,   SIGNAL(clicked()), m_history, SLOT(deleteCurrentPlaylist()));
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::onPlaylistChanged(Playlist *playlist)
{
    int index = m_history->playlists()->indexOf(playlist);
    ui->playlistCombo->setCurrentIndex(index);
}

void HistoryWidget::onCountChanged()
{
    if (m_history->playlists()->count() == 0)
        setEnabled(false);
    else
        setEnabled(true);

    int index = m_history->currentIndex();
    if (index == -1)
        ui->playlistCombo->setCurrentIndex(0);
    else
        ui->playlistCombo->setCurrentIndex(index);
}

void HistoryWidget::onCurrentIndexChanged(int index)
{
    if (index == -1)
        ui->playlistCombo->setCurrentIndex(m_history->currentIndex());
}
