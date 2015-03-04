#include "filesystemitemdelegate.h"

FileSystemItemDelegate::FileSystemItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_margin = 4;
}

void FileSystemItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize FileSystemItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    QSize size;
    size.setHeight(option.fontMetrics.height() + 2*m_margin);
    size.setWidth(16 + 2*m_margin + option.fontMetrics.width("..."));
    return size;
}
