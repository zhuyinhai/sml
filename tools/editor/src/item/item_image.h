#pragma once 

#include "item/item_base.h"
#include <QUrl>

class QGraphicsPixmapItem;

// -----------------------------------
//  ItemImage
// -----------------------------------
class ItemImage : public ItemBase
{
public:
	explicit ItemImage(const QUrl& url);
	virtual ~ItemImage(void) = default;

	QVariant getDecorationRole(void) const override;
	ItemType getItemType(void) const override;
	Qt::ItemFlags flags(void) const override;

	QGraphicsItem* getGraphicsItem(void) override;

private:
	QUrl url_;
	QGraphicsPixmapItem* pixmapItem_;
};
