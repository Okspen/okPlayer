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

    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        emit open(currentIndex());
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

    QModelIndex index = indexAt(event->pos());
    if (index.isValid() == false)
        return;

    bool isFile = index.data(FileSystemModel::IsFileRole).toBool();
    bool isFavorite = index.data(FileSystemModel::FavoriteRole).toBool();
    if (isFile) {
        QString favoriteText = (isFavorite) ? "Remove from Favorites" : "Add to Favorites";
        addToFavorites->setText(favoriteText);
    }
    QString path = index.data(FileSystemModel::FilePathRole).toString();

    QMenu *menu = (isFile) ? fileMenu : dirMenu;
    QAction* triggeredAction = menu->exec(mapToGlobal(event->pos()));
    if (triggeredAction == 0)
        return;

    FolderPlayer *folder = Player::instance()->folder();

    if (triggeredAction == replaceAllAction || triggeredAction == replaceAction)
        folder->play(path, true, false);

    if(triggeredAction == appendAllAction || triggeredAction == appendAction)
        folder->play(path, true, true);

    if(triggeredAction == replaceRootAction)
        folder->play(path, false, false);

    if(triggeredAction == appendRootAction)
        folder->play(path, false, true);

    if (triggeredAction == addToFavorites)
        model()->setData(index, !isFavorite, FileSystemModel::FavoriteRole);

    if(triggeredAction == openFolderAction) {
        QString folderPath =
            index.data(FileSystemModel::AbsolutePathRole).toString();
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
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
}

void FileSystemView::destroyContextMenus()
{
    delete fileMenu;
    delete dirMenu;

    delete appendAction;
    delete replaceAction;

    delete appendAllAction;
    delete appendRootAction;
    delete replaceAllAction;
    delete replaceRootAction;

    delete openFolderAction;
}
