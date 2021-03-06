#ifndef TIMELINEDELEGATE_H
#define TIMELINEDELEGATE_H

#include <QStyledItemDelegate>

class TimelineDelegate : public QStyledItemDelegate
{
public:
    TimelineDelegate(QObject *parent = nullptr);
    virtual ~TimelineDelegate(void) = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget* createEditor(
            QWidget* parent,
            const QStyleOptionViewItem& option,
            const QModelIndex& index) const override;

};

#endif // TIMELINEDELEGATE_H
