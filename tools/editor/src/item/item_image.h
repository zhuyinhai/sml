#pragma once 

#include "item/item_base.h"
#include <QUrl>

// -----------------------------------
//  ItemImage
// -----------------------------------
class ItemImage : public ItemBase
{
public:
	ItemImage(const QUrl& url);
	virtual ~ItemImage(void) = default;

	QVariant getDecorationRole(void) const override;
	ItemType getItemType(void) const override;
	Qt::ItemFlags flags(void) const override;

	QGraphicsItem* add(QGraphicsScene* graphicsScene) override;

private:
	QUrl url_;
};

