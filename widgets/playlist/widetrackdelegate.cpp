#include "widetrackdelegate.h"

WideTrackDelegate::WideTrackDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_margin = 4;
    m_active = false;
    m_star      = QIcon(":/tango/images/icons/tango/star_checked.png");
}

void WideTrackDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem localOption = option;

    bool isCurrent = index.data(PlaylistModel::CurrentRole).toBool();
    if (isCurrent) {
        localOption.state = localOption.state | QStyle::State_Selected;
        // to prevent becoming grey
        if (m_active)
            localOption.state = localOption.state | QStyle::State_Active;
    } else if (localOption.state & QStyle::State_Selected) {
        localOption.state = localOption.state & (~QStyle::State_Selected);
    }

    QStyle *style = localOption.widget->style();
    style->drawControl(QStyle::CE_ItemViewItem, &localOption, painter, localOption.widget);

    paintText(painter, option, index);
    paintFavorite(painter, option, index);
}

QSize WideTrackDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    QSize size;
    size.setHeight(option.fontMetrics.height()*2 + m_margin * 2);
    size.setWidth(option.fontMetrics.width("..."));
    return size;
}

bool WideTrackDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease) {

        QMouseEvent *mouseEvent = (QMouseEvent*) event;
        QPoint pos = mouseEvent->pos();

        if (mouseEvent->button() == Qt::LeftButton) {
            // if the star is hit
            if (pos.x() >= option.rect.right() - option.rect.height() - m_margin)
                model->setData(index, !index.data(PlaylistModel::FavoriteRole).toBool(), PlaylistModel::FavoriteRole);
            else
                model->setData(index, true, PlaylistModel::CurrentRole);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QIcon::Mode WideTrackDelegate::iconMode(const QModelIndex& index)
{
    bool isFavorite = index.data(PlaylistModel::FavoriteRole).toBool();
    return (isFavorite) ? QIcon::Normal : QIcon::Disabled;
}

void WideTrackDelegate::paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFont originalFont = painter->font();

    QString title = index.data(PlaylistModel::TitleRole).toString();
    QString album = index.data(PlaylistModel::AlbumRole).toString();
    QString artist = index.data(PlaylistModel::ArtistRole).toString();

    QRect rect(option.rect.left() + m_margin,
               option.rect.top()  + m_margin,
               option.rect.width() - m_margin - option.rect.height(),
               option.rect.height() - 2*m_margin);

    if (title.isEmpty()) {
        QString fileName = index.data(PlaylistModel::UrlRole).toUrl().fileName();
        painter->drawText(rect, Qt::AlignVCenter, fileName);
        return;
    }

    QRect textRect(option.rect.left() + m_margin,
                   option.rect.top() + m_margin,
                   option.rect.width() - m_margin - 2 * option.rect.height(),
                   painter->fontMetrics().height()+m_margin);

    QString titleText = option.fontMetrics.elidedText(title, Qt::ElideRight, textRect.width());

    /*QFont font = painter->font();

    font.setPixelSize(14);
    //font.setBold(true);
    painter->setFont(font);

    painter->drawText(textRect, elidedText);

    */QRect detailsRect(option.rect.left() + m_margin,
                      option.rect.top() + m_margin + textRect.height(),
                      option.rect.width() - m_margin - 2 * option.rect.height(),
                      painter->fontMetrics().height());

    QString detailsText = option.fontMetrics.elidedText(QString("%2 %3").arg(artist).arg((album.isEmpty())?"":"- "+album), Qt::ElideRight, detailsRect.width());

    /*font.setPixelSize(11);
    font.setBold(false);
    painter->setFont(font);

    painter->drawText(detailsRect, detailsText);

    painter->setFont(originalFont);*/

//    QStaticText staticText;
//    staticText.setTextWidth(option.rect.width());
//    staticText.setText(QString("<span style=\"font-size:13px\"><b>%1</b><br/>%2</span>").arg(titleText).arg(detailsText));
//    staticText.setTextFormat(Qt::RichText);

//    painter->drawStaticText(textRect.topLeft(), staticText);

    QTextDocument textDocument;
    //textDocument.setPageSize(QSizeF(400,100));
    textDocument.setHtml(QString("<b>%1</b><br/>%2 %3").arg(title).arg(artist).arg((album.isEmpty())?"":"- "+album));
    //textDocument.documentLayout()->setPaintDevice(painter->device());
    //painter->drawTextItem();
    textDocument.drawContents(painter, rect);


}

void WideTrackDelegate::paintFavorite(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect starRect(option.rect.right() - option.rect.height(),
                   option.rect.top(),
                   option.rect.height(),
                   option.rect.height());
    m_star.paint(painter, starRect, Qt::AlignCenter, WideTrackDelegate::iconMode(index), QIcon::On);
}

void WideTrackDelegate::setActive(bool active)
{
    m_active = active;
}
