#include "keyframelist.h"

#include <QDebug>
#include <QPainter>

#include "timelineeditor.h"
#include "global_setting.h"

#include "layer.h"
#include "composition.h"

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
    const Composition* composition = layer_->composition();

    QColor color(0, 0, 255, 255);
    QLine line(rect.topLeft(), rect.bottomLeft());
    for(int i=0; i<composition->frame(); ++i)
    {
        if( (i)%GLOBAL_SETTING.fps==0 )
        {
            color.setAlpha(255);
        }
        else
        {
            color.setAlpha(64);
        }
        painter->setPen(color);

        painter->drawLine(line);
        line.translate(composition->frameWidth(), 0);
    }

    painter->setBrush(QBrush(QColor("red")));
    for(auto& keyframe : *this)
    {
        painter->drawEllipse(QPoint(rect.left()+composition->frameWidth()*keyframe.frame, (rect.top()+rect.bottom())/2), 4, 4);
    }

}

bool KeyframeList::isEditing() const
{
    return isEditing_;
}

