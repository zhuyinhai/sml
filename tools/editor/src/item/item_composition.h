
#pragma once

#include <QList>
#include <QPointF>
#include <QSizeF>
#include <QColor>

#include "item/item_base.h"
#include "item/item_handle.h"

class QGraphicsScene;
class KeyframeModel;

// -----------------------------------
//  Layer
// -----------------------------------
struct Layer
{
	ItemHandle hItem;
	QString name;
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

	KeyframeModel* getKeyframeModel(void);

private:
	QGraphicsScene* graphicsScene_;
	QList<Layer> layers_;

	KeyframeModel* keyframeModel_;
};


