#include "timelineview.h"

#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>

#include "keyframelist.h"


CurrentTimeIndicator::CurrentTimeIndicator(QWidget* parent) :
    QWidget(parent)
{
    resize(5, 100);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}


void CurrentTimeIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor("blue"));
    painter.drawRect(rect());
    painter.setPen(QColor("red"));
    auto pos1 = this->pos();
    auto pos2 = pos1 + QPoint(0, size().height());
    painter.drawLine(pos1, pos2);
}




TimelineView::TimelineView(QWidget* parent) :
    QTreeView(parent)
{
    new CurrentTimeIndicator(this);
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



