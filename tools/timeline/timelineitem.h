#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H

#include <QStandardItem>

class Layer;
class KeyframeList;

class TimelineItem : public QStandardItem
{
public:
    TimelineItem(Layer* const layer);
    virtual ~TimelineItem(void);

private:
    KeyframeList* keyframeList_;
};



#endif // TIMELINEITEM_H
