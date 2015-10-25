#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QTreeView>
#include <QHeaderView>
#include <QScrollBar>

class QAction;
class Composition;

enum TimelineColumn : int
{
    NAME,
    VALUE,
    TIMELINE,
};


class CurrentTimeIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit CurrentTimeIndicator(QWidget* parent=nullptr);
    virtual ~CurrentTimeIndicator(void) = default;

public slots:
    void onTimelineResized(int left, int right);
    void onFrameWidthChanged(int frameWidth);
    void onScroll(int offset);

public:
    void updatePosition(void);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    int left_;
    int right_;
    int currentFrame_;
    int frameWidth_;
    int offset_;
    bool editing_;
};


class TimelineHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit TimelineHeaderView(QWidget* parent = nullptr);
    virtual ~TimelineHeaderView(void) = default;

protected:
    void paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const Q_DECL_OVERRIDE;
};


class CustomScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit CustomScrollBar(QWidget* parent = nullptr);
    virtual ~CustomScrollBar(void) = default;

    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

public slots:
    void onValueChanged(int value);

};


class TimelineView : public QTreeView
{
    Q_OBJECT
public:
    explicit TimelineView(QWidget* parent=nullptr);
    virtual ~TimelineView(void)=default;

    void init(void);

public slots:
    void onSectionResized(int logicalIndex, int oldSize, int newSize);
signals:
    void timelineResized(int left, int right);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent* event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent* event) Q_DECL_OVERRIDE;

private:
    void updateFrozenTreeGeometry(void);
    void updateTimelineWidth(void);
    Composition *composition(void);

private:
    QTreeView* frozenTreeView_;
    QAction* addKeyAction_;
    bool inContextMenu_;
};

#endif // TIMELINEVIEW_H
