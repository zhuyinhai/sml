#pragma once

#include "item/item_base.h"

// -----------------------------------
//  ItemComposition
// -----------------------------------
class ItemComposition : public ItemBase
{
public:
	ItemComposition(void) = default;
	virtual ~ItemComposition(void) = default;

	QVariant getDecorationRole(void) const override;
	ItemType getItemType(void) const override;
};

// -- inline implement ----------------- 

inline QVariant ItemComposition::getDecorationRole(void) const
{
	return QVariant();
}

inline ItemType ItemComposition::getItemType(void) const
{
	return ItemType::COMPOSITION;
}
