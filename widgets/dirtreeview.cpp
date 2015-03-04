#include "dirtreeview.h"

DirTreeView::DirTreeView(QWidget *parent) : QTreeView(parent)
{
    appendFileAction        = new QAction("Append", this);
    replaceFileAction       = new QAction("Replace", this);

    appendAllFilesAction    = new QAction("Append all", this);
    appendRootFilesAction   = new QAction("Append root", this);
    replaceAllFilesAction   = new QAction("Replace with all", this);
    replaceRootFilesAction  = new QAction("Replace with root", this);

    openFolderAction        = new QAction("Open containing folder", this);

    m_fsModel = new QFileSystemModel(this);
    m_fsModel->setNameFilterDisables(false);
    m_fsModel->setReadOnly(true);
    m_fsModel->setResolveSymlinks(false);
    m_fsModel->setNameFilters(PlayerSettings::nameFilters());

    setUniformRowHeights(true);
    setSortingEnabled(false);
    setUpdatesEnabled(false);
    setModel(m_fsModel);
    setUpdatesEnabled(true);

    setColumnHidden(1, true);
    setColumnHidden(2, true);
    setColumnHidden(3, true);
    setHeaderHidden(true);

    readSettings();
}

DirTreeView::~DirTreeView()
{
    writeSettings();
}

void DirTreeView::paintEvent(QPaintEvent *event)
{
    QTreeView::paintEvent(event);

    if (model() == 0) {
        QPainter painter(viewport());
        painter.drawText(rect(), Qt::AlignCenter, "Tree loading...");
    }
}

QString DirTreeView::currentPath() const
{
    return m_fsModel->filePath(currentIndex());
}

void DirTreeView::setCurrentPath(const QString &path)
{
    m_fsModel->setRootPath(path);
    setCurrentIndex(m_fsModel->index(path));
}

void DirTreeView::keyPressEvent(QKeyEvent *event)
{
    QTreeView::keyPressEvent(event);

    if(event->key() == Qt::Key_Return) {
        bool recursive = event->modifiers() & Qt::ControlModifier;
        QString path = selectionModel()->selectedIndexes().first().data(QFileSystemModel::FilePathRole).toString();
        Player::instance()->folder()->play(path, recursive, false);
    }
}

void DirTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    QTreeView::mouseReleaseEvent(event);

    if (event->button() == Qt::MidButton) {
        QString path = m_fsModel->filePath(indexAt(event->pos()));
        // Append
        //Player::instance()->folder()->play(path, true);
    }
}

void DirTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTreeView::mouseDoubleClickEvent(event);

    if (event->button() == Qt::LeftButton) {
        QString path = m_fsModel->filePath(indexAt(event->pos()));
        Player::instance()->folder()->play(path, true, false);
    }
}

void DirTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid() == false)
        return;

    bool isFile = !m_fsModel->isDir(index);
    QString path = m_fsModel->filePath(index);

    QMenu menu(this);
    if (isFile) {
        menu.addAction(appendFileAction);
        menu.addAction(replaceFileAction);
    } else {
        menu.addAction(appendAllFilesAction);
        menu.addAction(appendRootFilesAction);
        menu.addAction(replaceAllFilesAction);
        menu.addAction(replaceRootFilesAction);
    }

    QString folderPath;
    QModelIndex parentIndex = m_fsModel->parent(index);

    if (parentIndex.isValid()) {
        menu.addAction(openFolderAction);
        folderPath = m_fsModel->filePath(parentIndex);
    }

    QAction* triggeredAction = menu.exec(mapToGlobal(event->pos()));
    if (triggeredAction == 0)
        return;

    FolderPlayer *folder = Player::instance()->folder();

    if (triggeredAction == replaceAllFilesAction || triggeredAction == replaceFileAction)
        folder->play(path, true, false);

    if(triggeredAction == appendAllFilesAction || triggeredAction == appendFileAction)
        folder->play(path, true, true);

    if(triggeredAction == replaceRootFilesAction)
        folder->play(path, false, false);

    if(triggeredAction == appendRootFilesAction)
        folder->play(path, false, true);

    if(triggeredAction == openFolderAction)
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void DirTreeView::writeSettings()
{
    QSettings *settings = PlayerSettings::inst();
    settings->setValue("dirTree/currentPath", currentPath());
}

void DirTreeView::readSettings()
{
    QSettings *settings = PlayerSettings::inst();
    setCurrentPath(settings->value("dirTree/currentPath").toString());
}
