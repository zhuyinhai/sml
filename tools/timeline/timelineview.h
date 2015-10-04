#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QTreeView>

class TimelineView : public QTreeView
{
public:
    explicit TimelineView(QWidget* parent=nullptr);
    virtual ~TimelineView(void)=default;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // TIMELINEVIEW_H
