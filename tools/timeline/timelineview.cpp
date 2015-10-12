#include "timelineview.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

#include "keyframelist.h"


CurrentTimeIndicator::CurrentTimeIndicator(QWidget* parent) :
    QWidget(parent),
    left_(0),
    right_(0),
    editing_(false)
{
    resize(5, parent->height());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void CurrentTimeIndicator::onTimelineResized(int left, int right)
{
    left_ = left;
    right_ = right;
    setGeometry(left, 0, width(), height());
}


void CurrentTimeIndicator::paintEvent(QPaintEvent *)
{
    QWidget* parentWidget = qobject_cast<QWidget*>(parent());
    resize(width(), parentWidget->height());

    QPainter painter(this);
    painter.setBrush(QColor(0, 0, 255, 128));
    painter.drawRect(rect());
    auto pos1 = this->pos();
    auto pos2 = pos1 + QPoint(0, size().height());
    painter.drawLine(pos1, pos2);
}

void CurrentTimeIndicator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        editing_ = true;
    }
}

void CurrentTimeIndicator::mouseMoveEvent(QMouseEvent *event)
{
    if(editing_)
    {
        int x = mapToParent(event->pos()).x();
        setGeometry(qBound(left_, x, right_), 0, width(), height());
    }
}

void CurrentTimeIndicator::mouseReleaseEvent(QMouseEvent */*event*/)
{
    editing_ = false;
}



TimelineHeaderView::TimelineHeaderView(QWidget* parent) :
    QHeaderView(Qt::Horizontal, parent)
{
}

void TimelineHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if(TimelineColumn::TIMELINE==logicalIndex)
    {
        painter->setBrush(QColor("red"));
        painter->drawRect(rect);
    }
    else
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }
}




TimelineView::TimelineView(QWidget* parent) :
    QTreeView(parent),
    frozenTreeView_(new QTreeView(parent))
{}

void TimelineView::init()
{
    auto header = new TimelineHeaderView(this);
    auto cti = new CurrentTimeIndicator(this);
    setHeader( header );

    frozenTreeView_->setModel(model());
    frozenTreeView_->setFocusPolicy(Qt::NoFocus);
    //frozenTreeView_->header()->setSectionResizeMode(QHeaderView::Fixed);

    viewport()->stackUnder(frozenTreeView_);

    frozenTreeView_->setSelectionModel(selectionModel());
    for (int col = 2; col < model()->columnCount(); ++col)
          frozenTreeView_->setColumnHidden(col, true);

    frozenTreeView_->setColumnWidth(0, columnWidth(0));
    frozenTreeView_->setColumnWidth(1, columnWidth(1));
    frozenTreeView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTreeView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    updateFrozenTreeGeometry();

    // --
    connect( frozenTreeView_, SIGNAL(expanded(QModelIndex)), this, SLOT(expand(QModelIndex)) );
    connect( frozenTreeView_, SIGNAL(collapsed(QModelIndex)), this, SLOT(collapse(QModelIndex)) );

    // --
    connect( verticalScrollBar(), SIGNAL(valueChanged(int)), frozenTreeView_->verticalScrollBar(), SLOT(setValue(int)) );

    //--
    connect(header, SIGNAL(sectionResized(int,int,int)), this, SLOT(onSectionResized(int,int,int)));

    //--
    connect(this, SIGNAL(timelineResized(int,int)), cti, SLOT(onTimelineResized(int,int)));

}

void TimelineView::onSectionResized(int logicalIndex, int /*oldSize*/, int newSize)
{
    if(TimelineColumn::TIMELINE==logicalIndex)
    {
        int pos = header()->sectionPosition(TimelineColumn::TIMELINE);
        emit timelineResized(pos, pos + newSize);
    }
    else
    {
        frozenTreeView_->setColumnWidth(logicalIndex, newSize);
        updateFrozenTreeGeometry();
    }
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

void TimelineView::resizeEvent(QResizeEvent *event)
{
    QTreeView::resizeEvent(event);
    updateFrozenTreeGeometry();
}

void TimelineView::updateFrozenTreeGeometry()
{
    frozenTreeView_->setGeometry(frameWidth()+3,frameWidth()+3,
                                 columnWidth(0) + columnWidth(1),viewport()->height()+header()->height());
}



