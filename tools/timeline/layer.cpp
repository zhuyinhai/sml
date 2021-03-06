#include "layer.h"

#include <QStandardItem>
#include "timelineitem.h"
#include "composition.h"

Layer::Layer(const Composition* composition, const QString& text):
    composition_(composition)
{
    initialize(text);
}

const Composition* Layer::composition(void) const
{
    return composition_;
}


void Layer::initialize(const QString& text)
{
    auto root = new QStandardItem(text);
    auto dummy = new QStandardItem();
    dummy->setEditable(false);
    auto dummy2 = new QStandardItem();
    dummy2->setEditable(false);
    *this << root << dummy << dummy2;

    auto addParam = [root, this](const char* name, std::initializer_list<const char*> list ){
        auto param = new QStandardItem(name);
        param->setEditable(false);
        for( auto name : list )
        {
            auto nameItem = new QStandardItem(name);
            nameItem->setEditable(false);
            auto valueItem = new QStandardItem("0.0");
            auto timelineItem = new TimelineItem(this);
            param->appendRow(QList<QStandardItem*>() << nameItem << valueItem << timelineItem);
        }
        root->appendRow(QList<QStandardItem*>() << param );
    };

    addParam( "anchor", {"x","y"} );
    addParam( "position", {"x","y"} );
    addParam( "scale", {"x","y"} );
    addParam( "rotate", {"x", "y", "z"} );
    addParam( "color", {"r","g","b","a"} );
}
