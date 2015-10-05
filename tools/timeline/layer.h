#ifndef LAYER_H
#define LAYER_H

#include <QList>
#include <QString>
class QStandardItem;

class Layer : public QList<QStandardItem*>
{
public:
    explicit Layer(const QString& text);
    virtual ~Layer(void) = default;

    qreal duration(void) const;
    qreal timescale(void) const;

private:
    void initialize(const QString& text);
};

#endif // LAYER_H
