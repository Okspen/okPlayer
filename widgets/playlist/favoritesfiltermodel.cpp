#include "favoritesfiltermodel.h"

FavoritesFilterModel::FavoritesFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent), m_enabled(false)
{

}

FavoritesFilterModel::~FavoritesFilterModel()
{

}

bool FavoritesFilterModel::isEnabled() const
{
    return m_enabled;
}

void FavoritesFilterModel::setEnabled(bool enabled)
{
    emit beginResetModel();
    m_enabled = enabled;
    emit enabledChanged(m_enabled);
    emit endResetModel();
}

bool FavoritesFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_enabled)
        return sourceModel()->index(sourceRow, 0, sourceParent).data(PlaylistModel::FavoriteRole).toBool();
    else
        return true;
}

