#pragma once 

#include "item/item_base.h"
#include <QUrl>
#include <QVariant>

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

private:
	QIcon image_;
};


// -- inline implement -----------------

inline ItemImage::ItemImage(const QUrl& url)
	: image_(url.toLocalFile())
{}


inline QVariant ItemImage::getDecorationRole(void) const
{
	return image_;
}

inline ItemType ItemImage::getItemType(void) const
{
	return ItemType::IMAGE;
}