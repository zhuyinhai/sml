
#pragma once

#include <QList>
#include <QPointF>
#include <QSizeF>
#include <QColor>

#include "item/item_base.h"
#include "item/item_handle.h"

class QGraphicsScene;

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

	QGraphicsItem* add(QGraphicsScene* graphicsScene) override;

	QGraphicsScene* getGraphicsScene(void);
	void addItem(ItemHandle hItem);

private:

	struct Data
	{
		ItemHandle hItem;
		QPointF pos;
		QPointF anchor;
		QSizeF size;
		qreal rotate;
		QColor color;
	};

	QGraphicsScene* graphicsScene_;
	QSize size_;
	QList<Data> itemList_;
};


