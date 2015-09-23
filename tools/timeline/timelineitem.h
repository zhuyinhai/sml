#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H

#include <QStandardItem>
#include <QMetaClassInfo>

struct KeyframeData
{
    int frame;
    QVariant value;
};

class Layer;

class KeyframeList : public QList<KeyframeData>
{
public:
    KeyframeList(Layer* layer) :
        layer_(layer)
    {}
    void setMin( QVariant value ){ min_ = value; }
    void setMax( QVariant value ){ max_ = value; }
private:
    Layer* const layer_;
    QVariant max_;
    QVariant min_;
};

Q_DECLARE_METATYPE(KeyframeList*)


class TimelineItem : public QStandardItem
{
public:
    TimelineItem(Layer* const layer) :
        list_(layer)
    {
        setData( QVariant::fromValue(&list_) );
    }

    virtual ~TimelineItem(void) = default;
private:
    KeyframeList list_;
};

#endif // TIMELINEITEM_H
