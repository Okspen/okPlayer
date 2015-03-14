#include "filesystemview.h"

FileSystemView::FileSystemView(QWidget *parent) :
    QListView(parent)
{
    initContextMenus();
}

FileSystemView::~FileSystemView()
{
    destroyContextMenus();
}

void FileSystemView::keyReleaseEvent(QKeyEvent *event)
{
    QListView::keyReleaseEvent(event);

    QStringList pathes = selectedPathes();

    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:

        if (pathes.count() == 1)
            emit open(currentIndex());

        if (pathes.count() > 1) {

            if (event->modifiers() & Qt::ControlModifier)
                emit play(pathes, true);
            else
                emit play(pathes, true, true);
        }
        break;

    case Qt::Key_Back:
    case Qt::Key_Backspace:
        emit up();
        break;
    }
}

void FileSystemView::mouseReleaseEvent(QMouseEvent *event)
{
    QListView::mouseReleaseEvent(event);

    Qt::MouseButton button = event->button();
    if (button == Qt::XButton1)
        emit up();
}

void FileSystemView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QListView::mouseDoubleClickEvent(event);
    if (event->button() == Qt::LeftButton)
        emit open(currentIndex());
}

void FileSystemView::contextMenuEvent(QContextMenuEvent *event)
{
    if (model() == 0)
        return;

    QStringList pathes = selectedPathes();

    QMenu *menu = setupContextMenu();

    QAction* triggeredAction = menu->exec(mapToGlobal(event->pos()));
    if (triggeredAction == 0)
        return;

    if (triggeredAction == replaceAllAction || triggeredAction == replaceAction)
        emit play(pathes, true, false);

    if (triggeredAction == appendAllAction || triggeredAction == appendAction)
        emit play(pathes, true, true);

    if (triggeredAction == replaceRootAction)
        emit play(pathes, false, false);

    if (triggeredAction == appendRootAction)
        emit play(pathes, false, true);

    if (triggeredAction == addToFavorites) {
        QModelIndex index = indexAt(event->pos());
        bool isFavorite = index.data(FileSystemModel::FavoriteRole).toBool();
        model()->setData(index, !isFavorite, FileSystemModel::FavoriteRole);
    }

    if (triggeredAction == openFolderAction) {
        QModelIndex index = currentIndex();
        if (!index.isValid())
            return;

        QString path = index.data(FileSystemModel::AbsolutePathRole).toString();
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}

void FileSystemView::paintEvent(QPaintEvent *event)
{
    QListView::paintEvent(event);

    int rowCount = model()->rowCount();
    bool firstItemIsUp = model()->index(0,0).data(FileSystemModel::UpRole).toBool();
    if ((rowCount == 0) || (rowCount == 1 && firstItemIsUp)) {
        QPalette palette;
        QPainter painter(viewport());
        painter.setPen(palette.color(QPalette::Inactive, QPalette::Text));
        painter.drawText(
            rect(), Qt::AlignCenter | Qt::TextWordWrap, "Nothing to play here");
    }
}

void FileSystemView::initContextMenus()
{
    appendAction        = new QAction("Add", this);
    replaceAction       = new QAction("Play", this);

    appendAllAction     = new QAction("Add All", this);
    appendRootAction    = new QAction("Add Root", this);
    replaceAllAction    = new QAction("Play All", this);
    replaceRootAction   = new QAction("Play Root", this);

    addToFavorites      = new QAction("Add to Favorites", this);

    openFolderAction    = new QAction("Open Containing Folder", this);

    fileMenu = new QMenu(this);
    fileMenu->addAction(replaceAction);
    fileMenu->addAction(appendAction);
    fileMenu->addAction(addToFavorites);
    fileMenu->addAction(openFolderAction);

    dirMenu = new QMenu(this);
    dirMenu->addAction(replaceAllAction);
    dirMenu->addAction(replaceRootAction);
    dirMenu->addAction(appendAllAction);
    dirMenu->addAction(appendRootAction);    
    dirMenu->addAction(openFolderAction);

    multiMenu = new QMenu(this);
    multiMenu->addAction(replaceAction);
    multiMenu->addAction(appendAction);
    multiMenu->addAction(openFolderAction);
}

void FileSystemView::destroyContextMenus()
{
    delete fileMenu;
    delete dirMenu;
    delete multiMenu;

    delete appendAction;
    delete replaceAction;

    delete appendAllAction;
    delete appendRootAction;
    delete replaceAllAction;
    delete replaceRootAction;

    delete openFolderAction;
}

QMenu * FileSystemView::setupContextMenu()
{
    openFolderAction->setEnabled(true);

    QModelIndexList selected = selectedIndexes();
    int selectedCount = selected.count();

    if (selectedCount == 0) {

        appendAction->setEnabled(false);
        replaceAction->setEnabled(false);

        appendAllAction->setEnabled(false);
        appendRootAction->setEnabled(false);
        replaceAllAction->setEnabled(false);
        replaceRootAction->setEnabled(false);

        addToFavorites->setEnabled(false);
        return dirMenu;

    } else if (selectedCount == 1) {

        QModelIndex index = selected.at(0);

        bool isFile = index.data(FileSystemModel::IsFileRole).toBool();
        bool isFavorite = index.data(FileSystemModel::FavoriteRole).toBool();

        if (isFile) {

            QString favoriteText = (isFavorite) ? "Remove from Favorites" : "Add to Favorites";
            addToFavorites->setText(favoriteText);
            addToFavorites->setEnabled(true);

            appendAction->setEnabled(true);
            replaceAction->setEnabled(true);

            return fileMenu;

        } else {

            addToFavorites->setEnabled(false);

            appendAllAction->setEnabled(true);
            appendRootAction->setEnabled(true);
            replaceAllAction->setEnabled(true);
            replaceRootAction->setEnabled(true);

            return dirMenu;
        }

    } else if (selectedCount > 1) {

        appendAction->setEnabled(true);
        replaceAction->setEnabled(true);

        return multiMenu;
    }

    return dirMenu;
}

QStringList FileSystemView::selectedPathes() const
{
    QModelIndexList selected = selectedIndexes();
    QStringList pathes;

    for (int i=0; i < selected.count(); ++i)
        pathes << selected.at(i).data(FileSystemModel::FilePathRole).toString();

    return pathes;
}
