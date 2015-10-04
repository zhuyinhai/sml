#include "timelineitem.h"

#include "keyframelist.h"

TimelineItem::TimelineItem(Layer* const layer) :
    keyframeList_(new KeyframeList(layer))
{
    setData( QVariant::fromValue(keyframeList_) );
}

TimelineItem::~TimelineItem(void)
{
    delete keyframeList_;
}
