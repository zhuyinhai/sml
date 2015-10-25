#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <QList>
#include <QStandardItemModel>

class Layer;

class Composition : public QStandardItemModel
{
    Q_OBJECT
    using LayerList = QList<Layer*>;
public:
    Composition(QObject* parent=nullptr);
    virtual ~Composition(void);

    qreal duration(void) const;
    int frame(void) const;
    qreal timescale(void) const;
    int frameWidth(void) const;

    void setDuration(qreal duration);
    void setFrame(int frame);


    template<typename T, typename ...Args>
    void newLayer(Args... arg);

private:    
    LayerList layers_;
    int frame_;
    qreal timescale_;
};

template<typename T, typename ...Args>
void Composition::newLayer(Args... arg)
{
    auto layer = new T(this, std::forward<Args...>(arg...));
    appendRow(*layer);
    layers_.append(layer);
}




#endif // COMPOSITION_H
