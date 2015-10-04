#include "timelineview.h"

#include <QMouseEvent>

#include "keyframelist.h"

TimelineView::TimelineView(QWidget* parent) :
    QTreeView(parent)
{
}

void TimelineView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        QVariant variant = index.data(Qt::UserRole + 1);
        if(auto keyframeList = variant.value<KeyframeList*>())
        {
            if(!keyframeList->isEditing())
            {
                edit(index);
                return;
            }
        }
    }
    QTreeView::mousePressEvent(event);
}



