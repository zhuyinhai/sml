#include "timelinedelegate.h"

#include <QDebug>
#include <QPainter>
#include <QLineEdit>
#include <QValidator>

#include "timelineitem.h"


TimelineDelegate::TimelineDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

void TimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);

    QVariant variant = index.data(Qt::UserRole + 1);
    if( auto list = variant.value<KeyframeList*>() )
    {
        qDebug() << list->size();
    }
}

QSize TimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index);
}

QWidget* TimelineDelegate::createEditor(
        QWidget* parent,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const
{
    if( 1== index.column() )
    {
        QLineEdit* lineEdit = new QLineEdit(parent);
        lineEdit->setValidator(new QDoubleValidator(lineEdit));
        return lineEdit;
    }
    else
    {
        return QItemDelegate::createEditor(parent, option, index);
    }
}
