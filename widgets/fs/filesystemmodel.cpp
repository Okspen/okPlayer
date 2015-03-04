#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent) :
    QAbstractListModel(parent), m_favorites(0)
{
    m_dir.setFilter(m_dir.filter() | QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Drives);
    m_dir.setSorting(m_dir.sorting() | QDir::DirsFirst);
    m_iconProvider.setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_fileInfoList.count();
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (m_fileInfoList.isEmpty())
        return QVariant();

    if (index.isValid() == false)
        return QVariant();

    int row = qBound(0, index.row(), m_fileInfoList.count() - 1);
    QFileInfo info = m_fileInfoList.at(row);

    if (role == Qt::DisplayRole) {
        if (info.isRoot())
            return info.filePath().left(2); // Show drive name without ending '/'
        return info.fileName();
    }

    if (role == Qt::ToolTipRole)
        return info.filePath();

    if (role == Qt::DecorationRole)
        //return m_iconProvider.icon(info);
        //return m_iconCache.value(info.suffix());
        return (info.isDir()) ? m_iconProvider.icon(QFileIconProvider::Folder) : m_iconCache.value(info.suffix());
        //return QVariant();

    if (role == FavoriteRole) {
        if (!m_favorites) return false;
        QUrl url = QUrl::fromLocalFile(info.filePath());
        return m_favorites ? m_favorites->isFavorite(url) : false;
    }

    if (role == FileNameRole)
        return info.fileName();

    if (role == FilePathRole)
        return info.filePath();

    if (role == AbsolutePathRole)
        return info.absolutePath();

    if (role == UpRole)
        return false;

    if (role == IsFileRole)
        return info.isFile();

    return QVariant();
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QAbstractListModel::setData(index, value, role);

    if (!index.isValid())
        return false;

    if (role == FavoriteRole) {
        if (!m_favorites)
            return false;

        bool isFavorite = value.toBool();
        QUrl url = QUrl::fromLocalFile(index.data(FileSystemModel::FilePathRole).toString());

        isFavorite ? m_favorites->add(url) : m_favorites->remove(url);

        return true;
    }

    return false;
}

void FileSystemModel::setFavoritesManager(FavoritesManager *favorites)
{
    if (m_favorites) {
        disconnect(m_favorites, SIGNAL(added(QUrl)),    this,   SLOT(onMediaChanged(QUrl)));
        disconnect(m_favorites, SIGNAL(removed(QUrl)),  this,   SLOT(onMediaChanged(QUrl)));
    }

    if (favorites != 0) {
        m_favorites = favorites;
        connect(m_favorites,   SIGNAL(added(QUrl)),    this,   SLOT(onMediaChanged(QUrl)));
        connect(m_favorites,   SIGNAL(removed(QUrl)),  this,   SLOT(onMediaChanged(QUrl)));
    }
}

QDir FileSystemModel::dir() const
{
    return m_dir;
}

void FileSystemModel::cd(const QString &path)
{
    if (m_dir.cd(path)) {

        emit beginResetModel();

        m_fileInfoList.clear();
        m_fileInfoList.append(m_dir.entryInfoList());
        updateIconCache();

        emit endResetModel();

        emit pathChanged();
        emit upChanged(QDir(m_dir).cdUp());
    }
}

void FileSystemModel::cd(const QModelIndex &index)
{
    cd(index.data(FileNameRole).toString());
}

void FileSystemModel::cdUp()
{
    emit beginResetModel();

    QString prev = m_dir.dirName();
    if (m_dir.cdUp()) {
        m_prevDirName = prev;
        m_fileInfoList = m_dir.entryInfoList();
        updateIconCache();
    }

    emit endResetModel();

    emit pathChanged();
    emit upChanged(QDir(m_dir).cdUp());
}

void FileSystemModel::updateIconCache()
{
    QFileInfo info;
    for (int i = 0; i < m_fileInfoList.count(); i++) {
        info = m_fileInfoList.at(i);
        if (info.isFile() && !m_iconCache.contains(info.suffix()))
            m_iconCache.insert(info.suffix(), m_iconProvider.icon(info));
    }
}

void FileSystemModel::onMediaChanged(const QUrl &url)
{
    QFileInfo info(url.toLocalFile());
    int index = m_fileInfoList.indexOf(info);
    if (index == -1)
        return;

    emit dataChanged(createIndex(index,0),createIndex(index,0), QVector<int>() << FavoriteRole);
}

QFileInfo FileSystemModel::fileInfo(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= m_fileInfoList.count())
        return QFileInfo();

    return m_fileInfoList.at(index.row());
}

void FileSystemModel::setNameFilters(const QStringList &nameFilters)
{
    m_dir.setNameFilters(nameFilters);
}

QString FileSystemModel::currentPath() const
{
    return m_dir.absolutePath();
}

QString FileSystemModel::previousDirName() const
{
    return m_prevDirName;
}
