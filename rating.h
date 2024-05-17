#ifndef RATING_H
#define RATING_H

#include <QStyledItemDelegate>
#include <QPainter>

class Rating : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit Rating(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // RATING_H
