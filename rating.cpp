#include "rating.h"
#include <QRect>
#include <QPainter>
#include <QStyledItemDelegate>

Rating::Rating(QObject *parent): QStyledItemDelegate(parent)
{
}

void Rating::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().canConvert<int>()) {
        int rating = index.data().toInt();
        // Calculate bar rectangle
        QRect bar = option.rect.adjusted(1, 1, -1, -1);
        bar.setWidth(bar.width() * rating / 100.0);

        // The background
        painter->fillRect(option.rect, option.palette.dark());

        // The rating bar
        painter->fillRect(bar, option.palette.highlight());

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
