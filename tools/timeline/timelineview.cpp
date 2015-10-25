#include "timelineview.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QAction>
#include <QMenu>
#include <QTimerEvent>

#include "keyframelist.h"
#include "composition.h"

CurrentTimeIndicator::CurrentTimeIndicator(QWidget* parent) :
    QWidget(parent),
    left_(0),
    right_(0),
    currentFrame_(0),
    frameWidth_(0),
    offset_(0),
    editing_(false)
{
    resize(5, parent->height());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void CurrentTimeIndicator::onTimelineResized(int left, int right)
{
    left_ = left;
    right_ = right;
    updatePosition();
}

void CurrentTimeIndicator::onFrameWidthChanged(int frameWidth)
{
    frameWidth_ = frameWidth;
    updatePosition();
}

void CurrentTimeIndicator::onScroll(int offset)
{
    offset_ = offset;
    updatePosition();
}

void CurrentTimeIndicator::updatePosition()
{
    setGeometry(left_+frameWidth_*currentFrame_-offset_, 0, width(), height());
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
        x -= x%frameWidth_;
        currentFrame_ = qBound(0, (x-left_+offset_)/frameWidth_, right_/frameWidth_);
        updatePosition();
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
#if 0
    if(TimelineColumn::TIMELINE==logicalIndex)
    {
        painter->setBrush(QColor("red"));
        painter->drawRect(rect);
    }
    else
#endif
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }
}

CustomScrollBar::CustomScrollBar(QWidget *parent):
    QScrollBar(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

bool CustomScrollBar::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << event;
    return QScrollBar::eventFilter(obj, event);
}

void CustomScrollBar::onValueChanged(int value)
{
    qDebug() << value;
}



TimelineView::TimelineView(QWidget* parent) :
    QTreeView(parent),
    frozenTreeView_(new QTreeView(parent)),
    addKeyAction_(new QAction(tr("&Add Key"),this)),
    inContextMenu_(false)
{
}

void TimelineView::init()
{

    setHorizontalScrollBar(new CustomScrollBar(this));

    auto header = new TimelineHeaderView(this);
    setHeader( header );

    auto cti = new CurrentTimeIndicator(this);
    if(Composition * comp = composition())
    {
        cti->onFrameWidthChanged(comp->frameWidth());
    }


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
    connect( frozenTreeView_->verticalScrollBar(), SIGNAL(valueChanged(int)), verticalScrollBar(), SLOT(setValue(int)) );

    connect( horizontalScrollBar(), SIGNAL(valueChanged(int)), cti, SLOT(onScroll(int)) );

    //--
    connect(header, SIGNAL(sectionResized(int,int,int)), this, SLOT(onSectionResized(int,int,int)));

    //--
    connect(this, SIGNAL(timelineResized(int,int)), cti, SLOT(onTimelineResized(int,int)));

    updateTimelineWidth();
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

void TimelineView::contextMenuEvent(QContextMenuEvent *event)
{
    inContextMenu_ = true;
    QMenu menu(this);
    menu.addAction(addKeyAction_);
    QAction* action = menu.exec(event->globalPos());
    if(action==addKeyAction_)
    {
        QModelIndex index = indexAt(event->pos());
        QVariant variant = index.data(Qt::UserRole + 1);
        if( auto keyframeList = variant.value<KeyframeList*>() )
        {
            qDebug() << event->pos().x();
            QPoint point = mapFromGlobal(event->globalPos());
            qDebug() << point.x();
            KeyframeData data;
            data.frame = 3;
            data.value = 0;
            keyframeList->append(data);
        }
    }
    inContextMenu_ = false;
}

void TimelineView::timerEvent(QTimerEvent *event)
{
    // timerEvent move horitontal scrollBar after mouse right click
    event->ignore();
#if 0
    if( inContextMenu_ )
    {
        event->ignore();
    }
    else
    {
        QTreeView::timerEvent(event);
    }
#endif
}


void TimelineView::updateFrozenTreeGeometry()
{
    frozenTreeView_->setGeometry(frameWidth()+3,frameWidth()+3,
                                 columnWidth(0) + columnWidth(1),viewport()->height()+header()->height());
}

void TimelineView::updateTimelineWidth()
{
    Composition* comp = composition();
    if(!comp)
    {
        return;
    }
    header()->resizeSection(TimelineColumn::TIMELINE, comp->frame() * comp->frameWidth());
}

Composition *TimelineView::composition()
{
    return static_cast<Composition*>(model());
}




