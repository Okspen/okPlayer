#ifndef WIDETRACKDELEGATE_H
#define WIDETRACKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QSortFilterProxyModel>
#include <QStaticText>
#include <QTextDocument>
#include "widgets/playlist/playlistmodel.h"

class WideTrackDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit WideTrackDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    bool isActive() const;
    void setActive(bool active);

protected:
    bool    m_active;
    int     m_margin;
    QIcon   m_star;

    static QIcon::Mode iconMode(const QModelIndex &index);
    void paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintFavorite(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // WIDETRACKDELEGATE_H
