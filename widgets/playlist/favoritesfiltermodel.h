#ifndef FAVORITESFILTERMODEL_H
#define FAVORITESFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "widgets/playlist/playlistmodel.h"

class FavoritesFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FavoritesFilterModel(QObject *parent = 0);
    ~FavoritesFilterModel();

    bool isEnabled() const;

signals:
    void enabledChanged(bool);

public slots:
    void setEnabled(bool enabled);

protected:
     bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
     bool m_enabled;
};

#endif // FAVORITESFILTERMODEL_H
