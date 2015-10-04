#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include <QWidget>
#include <QVariant>

class KeyframeList;

class TimelineEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineEditor(KeyframeList* const keyframeList,QWidget *parent = nullptr);
    virtual ~TimelineEditor(void);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    KeyframeList* const keyframeList_;
};


#endif // TIMELINEEDITOR_H
