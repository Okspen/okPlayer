#ifndef FILESYSTEMITEMDELEGATE_H
#define FILESYSTEMITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class FileSystemItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FileSystemItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    int     m_margin;
};

#endif // FILESYSTEMITEMDELEGATE_H
