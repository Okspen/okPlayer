#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QFileIconProvider>
#include <QTime>
#include <QMimeData>
#include "player/player.h"

class FileSystemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FileRoles {
        UpRole          = Qt::UserRole + 1,
        IsFileRole      = Qt::UserRole + 2,
        FileNameRole    = Qt::UserRole + 3,
        FilePathRole    = Qt::UserRole + 4,
        AbsolutePathRole = Qt::UserRole + 5,
        FavoriteRole    = Qt::UserRole + 6
    };

    explicit FileSystemModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;

    void setFavoritesManager(FavoritesManager *favorites);

    QDir        dir() const;
    QFileInfo   fileInfo(const QModelIndex &index) const;
    QString currentPath() const;
    QString previousDirName() const;

    void setNameFilters(const QStringList &nameFilters);

signals:
    void pathChanged();
    void upChanged(bool);

public slots:
    void cd(const QString &path);
    void cd(const QModelIndex &index);
    void cdUp();

private:
    QDir                m_dir;
    QFileInfoList       m_fileInfoList;
    QFileIconProvider   m_iconProvider;
    QString             m_prevDirName;
    QMap<QString, QIcon> m_iconCache;
    FavoritesManager    *m_favorites;

    void updateIconCache();

private slots:
    void onMediaChanged(const QUrl &url);
};

#endif // FILESYSTEMMODEL_H
