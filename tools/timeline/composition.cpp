#include "composition.h"
#include "layer.h"
#include "global_setting.h"

Composition::Composition(QObject* parent) :
    QStandardItemModel(parent),
    frame_(0),
    timescale_(1.0)
{
    QStringList headerLabels = { "layer", "value", "timeline" };
    setHorizontalHeaderLabels( headerLabels );
}

Composition::~Composition(void)
{
    qDeleteAll(layers_);
}

qreal Composition::duration(void) const
{
    return frame()*GLOBAL_SETTING.fps;
}

int Composition::frame(void) const
{
    return frame_;
}

qreal Composition::timescale(void) const
{
    return timescale_;
}

int Composition::frameWidth(void) const
{
    static const int kDefaultWidth = 8;
    return static_cast<int>(std::ceil(timescale()*kDefaultWidth));
}

void Composition::setDuration(qreal duration)
{
    setFrame( static_cast<int>(duration*GLOBAL_SETTING.fps) );
}

void Composition::setFrame(int frame)
{
    frame_ = frame;
}


