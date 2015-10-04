#ifndef KEYFRAMELIST_H
#define KEYFRAMELIST_H

#include <QList>
#include <QMetaType>
#include <QVariant>

class Layer;
class QWidget;
class QPainter;

struct KeyframeData
{
    int frame;
    QVariant value;
};


class KeyframeList : public QList<KeyframeData>
{
    friend class TimelineEditor;
public:
    KeyframeList(Layer* const layer);
    virtual ~KeyframeList(void) = default;

    void setMin( QVariant value );
    void setMax( QVariant value );

    QWidget* createEditor(QWidget* parent);

    void paint(QPainter *painter, const QRect &rect,const QPalette &palette) const;

    bool isEditing(void) const;

private:
    Layer* const layer_;
    QVariant max_;
    QVariant min_;
    bool isEditing_;
};

Q_DECLARE_METATYPE(KeyframeList*)

#endif // KEYFRAMELIST_H
