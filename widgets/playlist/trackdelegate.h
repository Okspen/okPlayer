#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QSortFilterProxyModel>
#include "widgets/playlist/playlistmodel.h"

class TrackDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TrackDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    bool isActive() const;
    void setActive(bool active);

protected:
    bool    m_active;
    int     m_margin;
    QIcon   m_star;
    QIcon   m_current;

    static QIcon::Mode iconMode(const QModelIndex &index);
};

#endif // TRACKDELEGATE_H
