#include "timelineeditor.h"

#include <QPainter>
#include <QDebug>
#include "keyframelist.h"


TimelineEditor::TimelineEditor(KeyframeList* const keyframeList,QWidget *parent) :
    QWidget(parent),
    keyframeList_(keyframeList)
{
    qDebug() << "create editor";
    keyframeList_->isEditing_ = true;
}

TimelineEditor::~TimelineEditor()
{
    qDebug() << "destroy editor";
    keyframeList_->isEditing_ = false;
}

void TimelineEditor::paintEvent(QPaintEvent *)
{
    // KeyframeList::paint() called from TimelineDelegate.
#if 0
    QPainter painter(this);
    keyframeList_->paint( &painter, rect(), palette() );
#endif
}

void TimelineEditor::mouseMoveEvent(QMouseEvent *)
{

}

void TimelineEditor::mouseReleaseEvent(QMouseEvent *)
{

}

