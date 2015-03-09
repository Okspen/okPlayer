#include "trackdelegate.h"

TrackDelegate::TrackDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_margin    = 4;
    m_active    = false;
    m_star      = QIcon(":/tango/images/icons/tango/star_checked.png");
}

void TrackDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    /* Painting background */

    QStyleOptionViewItem localOption = option;

    bool isCurrent = index.data(PlaylistModel::CurrentRole).toBool();
    if (isCurrent) {
        localOption.state = localOption.state | QStyle::State_Selected;
        // to prevent becoming grey
        if (m_active)
            localOption.state = localOption.state | QStyle::State_Active;
    } else if (localOption.state & QStyle::State_Selected) {
        //localOption.state = localOption.state & (~QStyle::State_Selected);
    }

    QStyle *style = localOption.widget->style();
    style->drawControl(QStyle::CE_ItemViewItem, &localOption, painter, localOption.widget);

    /* Painting time */

    QString time = index.data(PlaylistModel::DurationRole).toString();
    int timeWidth = option.fontMetrics.width(time);

    QRect timeRect(option.rect.right() - m_margin - option.rect.height() - m_margin - timeWidth,
                    option.rect.top(),
                    timeWidth,
                    option.rect.height());
    painter->drawText(timeRect, Qt::AlignCenter, time);

    /* Painting favorite */

    QRect favoriteRect(option.rect.right() - option.rect.height(),
                        option.rect.top(),
                        option.rect.height(),
                        option.rect.height());
    m_star.paint(painter, favoriteRect, Qt::AlignCenter, TrackDelegate::iconMode(index), QIcon::On);

    /* Painting track details */

    QRect textRect(option.rect.left() + m_margin,
                    option.rect.top() + m_margin,
                    option.rect.width() - 4 * m_margin - favoriteRect.width() - timeRect.width(),
                    option.rect.height());
    QString mainText = index.data(Qt::DisplayRole).toString();
    QString elidedText = option.fontMetrics.elidedText(mainText, Qt::ElideRight, textRect.width());

    painter->drawText(textRect, elidedText);

//    if (index.row() % 4 == 0) {
//        painter->save();
//        painter->setOpacity(0.9);
//        painter->setPen(Qt::white);
//        painter->setBrush(QBrush(Qt::white));
//        painter->drawRect(option.rect);
//        painter->setOpacity(1.0);
//        painter->setBrush(QBrush(Qt::red));
//        painter->setPen(QPen(Qt::red));
//        painter->drawText(textRect, Qt::AlignHCenter, "Error: File not available");
//        painter->restore();
//    }
}

QSize TrackDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    QSize size;
    size.setHeight(option.fontMetrics.height() + m_margin * 2);
    size.setWidth(option.fontMetrics.width("..."));
    return size;
}

bool TrackDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        model->setData(index, true, PlaylistModel::CurrentRole);
        return true;
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = (QMouseEvent*) event;
        QPoint pos = mouseEvent->pos();

        if (mouseEvent->button() == Qt::LeftButton) {
            // if user hits the star
            if (pos.x() >= option.rect.right() - option.rect.height() - m_margin)
                model->setData(index, !index.data(PlaylistModel::FavoriteRole).toBool(), PlaylistModel::FavoriteRole);

            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QIcon::Mode TrackDelegate::iconMode(const QModelIndex& index)
{
    bool isFavorite = index.data(PlaylistModel::FavoriteRole).toBool();
    return (isFavorite) ? QIcon::Normal : QIcon::Disabled;
}

void TrackDelegate::setActive(bool active)
{
    m_active = active;
}
