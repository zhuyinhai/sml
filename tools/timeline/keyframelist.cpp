#include "keyframelist.h"

#include <QDebug>
#include <QPainter>
#include "timelineeditor.h"

KeyframeList::KeyframeList(Layer* const layer) :
    layer_(layer),
    isEditing_(false)
{}

void KeyframeList::setMin( QVariant value )
{
    min_ = value;
}

void KeyframeList::setMax( QVariant value )
{
    max_ = value;
}

QWidget* KeyframeList::createEditor(QWidget* parent)
{
    return new TimelineEditor(this, parent);
}

void KeyframeList::paint(QPainter *painter, const QRect &rect, const QPalette &/*palette*/) const
{
    QColor color(255, 0, 0, 128);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);
}

bool KeyframeList::isEditing() const
{
    return isEditing_;
}

