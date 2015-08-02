
#pragma once

#include <QList>
#include <QPointF>
#include <QSizeF>
#include <QColor>

#include "item/item_base.h"
#include "item/item_handle.h"

class QGraphicsScene;

// -----------------------------------
//  Layer
// -----------------------------------
struct Layer
{
	ItemHandle hItem;
	QPointF position;
	QPointF anchor;
	QSizeF scale;
	qreal rotate;
	QColor color;

	QGraphicsItem* itemPtr;
};



// -----------------------------------
//  ItemComposition
// -----------------------------------
class ItemComposition : public ItemBase
{
public:
	ItemComposition(void);
	virtual ~ItemComposition(void);

	QVariant getDecorationRole(void) const override;
	ItemType getItemType(void) const override;
	Qt::ItemFlags flags(void) const override;

	QGraphicsItem* getGraphicsItem(void) override;

	QGraphicsScene* getGraphicsScene(void);
	void addItem(ItemHandle hItem);

private:
	QGraphicsScene* graphicsScene_;
	QList<Layer> layers_;
};


