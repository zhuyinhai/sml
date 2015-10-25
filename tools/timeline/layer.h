#ifndef LAYER_H
#define LAYER_H

#include <QList>
#include <QString>

class Composition;
class QStandardItem;

class Layer : public QList<QStandardItem*>
{
public:
    explicit Layer(const Composition* composition, const QString& text);
    virtual ~Layer(void) = default;

    const Composition* composition(void) const;

private:
    void initialize(const QString& text);

private:
    const Composition* const composition_;

};

#endif // LAYER_H
