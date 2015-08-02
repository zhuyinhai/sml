#pragma once

#include <QApplication>
#include <QStyle>

#include "item/item_base.h"

// -----------------------------------
//  ItemFolder
// -----------------------------------
class ItemFolder : public ItemBase
{
public:
	ItemFolder(void) = default;
	virtual ~ItemFolder(void) = default;

	QVariant getDecorationRole(void) const override;
	ItemType getItemType(void) const override;
	Qt::ItemFlags flags(void) const override;

	QGraphicsItem* getGraphicsItem(void) override;
};


// -- inline implement ----------------- 

inline QVariant ItemFolder::getDecorationRole(void) const
{
	return QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon);
}

inline ItemType ItemFolder::getItemType(void) const
{
	return ItemType::FOLDER;
}

inline Qt::ItemFlags ItemFolder::flags(void) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

inline QGraphicsItem* ItemFolder::getGraphicsItem(void)
{
	return nullptr;
}
