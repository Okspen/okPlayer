#include "playlistwidget.h"
#include "ui_playlistwidget.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);

    m_delegate = new TrackDelegate(this);
    ui->listView->setItemDelegate(m_delegate);
    ui->listView->setAcceptDrops(true);

    m_model = new PlaylistModel(this);
    m_model->setTrackCycler(Player::instance()->cycler());
    m_model->setMediaLibrary(Player::instance()->media());
    m_model->setFavoritesManager(Player::instance()->favorites());

    m_favFilterModel = new FavoritesFilterModel(this);
    m_favFilterModel->setSourceModel(m_model);
    m_favFilterModel->setDynamicSortFilter(true);
    connect(ui->listView,       SIGNAL(showFavoritesToggled(bool)), this,           SLOT(setFavoritesFilterEnabled(bool)));
    connect(ui->listView,       SIGNAL(scrollToCurrentToggled()),   this,           SLOT(scrollToCurrent()));
    connect(m_favFilterModel,   SIGNAL(enabledChanged(bool)),       ui->listView,   SLOT(toggleFavorites(bool)));

    m_sortModel = new QSortFilterProxyModel(this);
    m_sortModel->setSourceModel(m_favFilterModel);
    m_sortModel->setFilterRole(PlaylistModel::SearchRole);
    m_sortModel->setDynamicSortFilter(true);
    m_sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->listView->setModel(m_sortModel);

    connect(ui->clearButton,    SIGNAL(clicked()),              ui->filterEdit, SLOT(clear()));
    connect(ui->filterEdit,     SIGNAL(textChanged(QString)),   this,           SLOT(setFilter(QString)));

    TrackCycler * cycler = Player::instance()->cycler();
    if (cycler != 0) {
        m_cycler = cycler;
        connect(cycler, SIGNAL(trackChanged(PlayId,PlayId)), this, SLOT(onTrackChanged(PlayId,PlayId)));
    } else {
        m_cycler = 0;
    }

    PlaylistHistory *history = Player::instance()->history();
    if (history != 0) {
        connect(history,SIGNAL(currentChanged(Playlist*)),  this,   SLOT(setPlaylist(Playlist*)));
        connect(history,SIGNAL(countChanged()),             this,   SLOT(onPlaylistCountChanged()));
        setPlaylist(history->current());
    }
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::setPlaylist(Playlist *playlist)
{
    if (playlist != 0)
        connect (playlist, SIGNAL(destroyed()), this, SLOT(onPlaylistDestroyed()));

    PlayId current = Player::instance()->cycler()->current();
    if (current.playlist() == playlist)
        ui->listView->scrollTo(
            sortIndex(current.index()), QAbstractItemView::PositionAtCenter);
    else
        ui->listView->scrollToTop();

    ui->filterEdit->clear();
    m_favFilterModel->setEnabled(false);
    ui->listView->setEmptyMessage(chooseEmptyMessage());
    ui->listView->setFavoritesEnabled(playlist != 0);
}

void PlaylistWidget::setFilter(const QString &pattern)
{
    m_sortModel->setFilterFixedString(pattern);
    ui->listView->scrollTo(sortIndex(
            Player::instance()->cycler()->current().index()),
            QAbstractItemView::PositionAtCenter);

    ui->listView->setEmptyMessage(chooseEmptyMessage());
    ui->listView->viewport()->update();
}

void PlaylistWidget::setFavoritesFilterEnabled(bool enabled)
{
    m_favFilterModel->setEnabled(enabled);
    if (enabled) {
        ui->listView->setEmptyMessage("No Favorites in this playlist");
    }

    int index = Player::instance()->cycler()->current().index();
    ui->listView->scrollTo(sortIndex(index), QAbstractItemView::PositionAtCenter);
}

QModelIndex PlaylistWidget::sortIndex(int row) const
{
    QModelIndex index       = m_model->index(row);
    QModelIndex favIndex    = m_favFilterModel->mapFromSource(index);
    return m_sortModel->mapFromSource(favIndex);
}

QString PlaylistWidget::chooseEmptyMessage() const
{
    if (m_model->playlist() == 0)
        return "No Playlist";

    if (!m_sortModel->filterRegExp().isEmpty())
        return "No results for: "+m_sortModel->filterRegExp().pattern();

    if (m_favFilterModel->isEnabled())
        return "No Favorites in this playlist";

    return "Empty Playlist";
}

void PlaylistWidget::onTrackChanged(PlayId prevId, PlayId curId)
{
    if (m_model->playlist() == curId.playlist())
        ui->listView->scrollTo(sortIndex(curId.index()), QAbstractItemView::EnsureVisible);
}

void PlaylistWidget::onPlaylistCountChanged()
{
    ui->listView->setEmptyMessage(chooseEmptyMessage());
}

void PlaylistWidget::onPlaylistDestroyed()
{
    ui->listView->setFavoritesEnabled(false);
}

void PlaylistWidget::scrollToCurrent()
{
    if (m_cycler)
        ui->listView->scrollTo(sortIndex(m_cycler->currentIndex()), QAbstractItemView::PositionAtCenter);
}
