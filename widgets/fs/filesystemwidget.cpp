#include "filesystemwidget.h"
#include "ui_filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemWidget)
{
    ui->setupUi(this);

    m_delegate = new FileSystemItemDelegate(this);
    ui->listView->setItemDelegate(m_delegate);

    initModel();
    ui->listView->setModel(m_sortModel);
    connect(ui->listView, SIGNAL(open(QModelIndex)),m_model, SLOT(cd(QModelIndex)));
    connect(ui->listView, SIGNAL(up()),             m_model, SLOT(cdUp()));
    connect(ui->listView, SIGNAL(play(QStringList,bool,bool)), this, SLOT(play(QStringList,bool,bool)));

    initSearch();

    ui->progressPanel->hide();

    connect(ui->upButton,       SIGNAL(clicked()),      m_model,        SLOT(cdUp()));
    connect(m_model,            SIGNAL(upChanged(bool)),ui->upButton,   SLOT(setEnabled(bool)));
    connect(m_model,            SIGNAL(pathChanged()),  this,           SLOT(onPathChanged()));
    connect(ui->selectButton,   SIGNAL(clicked()),      this,           SLOT(selectFolder()));

    connect(ui->playAllButton,  SIGNAL(clicked()), this,    SLOT(playAll()));
    connect(ui->playRootButton, SIGNAL(clicked()), this,    SLOT(playRoot()));

    connect(ui->addAllButton,   SIGNAL(clicked()), this,    SLOT(addAll()));
    connect(ui->addRootButton,  SIGNAL(clicked()), this,    SLOT(addRoot()));

    m_scanDialog = new ScanProgressDialog(this);
    connect(m_scanDialog,                   SIGNAL(cancelled()),                Player::instance()->folder(), SLOT(cancel()));
    connect(Player::instance()->folder(),   SIGNAL(cancelled()),                m_scanDialog,       SLOT(onScanCancelled()));
    connect(Player::instance()->folder(),   SIGNAL(scanPathChanged(QString)),   m_scanDialog,       SLOT(setScanPath(QString)));
    connect(Player::instance()->folder(),   SIGNAL(finished(int)),              m_scanDialog,       SLOT(onScanFinished(int)));

    m_scanDialogTimer.setSingleShot(true);
    connect(&m_scanDialogTimer,             SIGNAL(timeout()),                  this,               SLOT(showScanDialog()));
    connect(Player::instance()->folder(),   SIGNAL(finished(int)),              &m_scanDialogTimer, SLOT(stop()));
}

void FileSystemWidget::cd(const QString &path)
{
    m_model->cd(path);
}

QString FileSystemWidget::currentPath() const
{
    return m_model->currentPath();
}

FileSystemWidget::~FileSystemWidget()
{
    delete ui;
}

void FileSystemWidget::setFocusOnFilter()
{
    ui->filterEdit->setFocus();
}

void FileSystemWidget::dragEnterEvent(QDragEnterEvent *event)
{
    int urlCount = event->mimeData()->urls().count();
    if (urlCount == 0 || urlCount > 1)
        return;

    event->accept();
}

void FileSystemWidget::dragMoveEvent(QDragMoveEvent *event)
{
    int urlCount = event->mimeData()->urls().count();
    if (urlCount == 0 || urlCount > 1)
        return;

    event->accept();
}

void FileSystemWidget::dropEvent(QDropEvent *event)
{
    const QMimeData * data = event->mimeData();

    QList<QUrl> urls    = data->urls();
    int urlCount        = urls.count();

    if (urlCount == 0 || urlCount > 1 )
        return;

    if (urlCount == 1) {
        QUrl url = urls.at(0);
        QFileInfo fileInfo(url.toLocalFile());
        if (fileInfo.exists() && fileInfo.isDir()) {
            m_model->cd(fileInfo.filePath());
            event->accept();
        }
    }
}

void FileSystemWidget::initModel()
{
    m_model = new FileSystemModel(this);
    m_model->setNameFilters(PlayerSettings::nameFilters());
    m_model->setFavoritesManager(Player::instance()->favorites());

    m_sortModel = new QSortFilterProxyModel(this);
    m_sortModel->setSourceModel(m_model);
    m_sortModel->setDynamicSortFilter(true);
    m_sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void FileSystemWidget::initSearch()
{
    connect(ui->filterEdit, SIGNAL(textChanged(QString)),   m_sortModel,    SLOT(setFilterFixedString(QString)));
    connect(m_model,        SIGNAL(pathChanged()),          ui->filterEdit, SLOT(clear()));
    connect(ui->clearButton,SIGNAL(clicked()),              ui->filterEdit, SLOT(clear()));
}

void FileSystemWidget::playAll()
{
    Player::instance()->folder()->play(m_model->currentPath(), true);
    m_scanDialogTimer.start(200);
}

void FileSystemWidget::playRoot()
{
    Player::instance()->folder()->play(m_model->currentPath(), false);
    m_scanDialogTimer.start(200);
}

void FileSystemWidget::addAll()
{
    Player::instance()->folder()->play(m_model->currentPath(), true, true);
    m_scanDialogTimer.start(200);
}

void FileSystemWidget::addRoot()
{
    Player::instance()->folder()->play(m_model->currentPath(), false, true);
    m_scanDialogTimer.start(200);
}

void FileSystemWidget::play(const QStringList &pathes, bool recursive, bool append)
{
    Player::instance()->folder()->play(pathes, recursive, append);
    m_scanDialogTimer.start(200);
}

void FileSystemWidget::selectFolder()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Open Directory"),
        m_model->currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_model->cd(dir);
}

void FileSystemWidget::showScanDialog()
{
    m_scanDialog->show();
}

void FileSystemWidget::onPathChanged()
{
    int row = m_model->dir().entryList().indexOf(m_model->previousDirName());

    if (row != -1) {
        QModelIndex index = m_sortModel->mapFromSource(m_model->index(row, 0));
        ui->listView->setCurrentIndex(index);
        ui->listView->scrollTo(index, QAbstractItemView::PositionAtCenter);
    } else {
        if (m_model->rowCount(QModelIndex()) != 0) {
            QModelIndex index = m_sortModel->mapFromSource(m_model->index(0, 0));
            ui->listView->setCurrentIndex(index);
        }
        ui->listView->scrollToTop();
    }
}
