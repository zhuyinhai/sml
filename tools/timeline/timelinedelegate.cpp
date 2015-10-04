#include "timelinedelegate.h"

#include <QDebug>
#include <QPainter>
#include <QLineEdit>
#include <QValidator>

#include "keyframelist.h"


TimelineDelegate::TimelineDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void TimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant variant = index.data(Qt::UserRole + 1);
    if( auto keyframeList = variant.value<KeyframeList*>() )
    {
        keyframeList->paint(painter, option.rect, option.palette);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize TimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
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
        QVariant variant = index.data(Qt::UserRole + 1);
        if( auto keyframeList = variant.value<KeyframeList*>() )
        {
            return keyframeList->createEditor(parent);
        }

        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}
