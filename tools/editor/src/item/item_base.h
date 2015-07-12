#pragma once

#include <QVariant>

class QGraphicsItem;
class QGraphicsScene;

// -----------------------------------
//  ItemType
// -----------------------------------
enum class ItemType
{
	FOLDER,
	IMAGE,
	COMPOSITION,
	PLANE,
	
	ITEM_TYPE_MAX
};

// -----------------------------------
//  ItemBase
// -----------------------------------
class ItemBase
{
public:
	virtual ~ItemBase(void) = default;

	virtual QVariant getDecorationRole(void) const = 0;
	virtual ItemType getItemType(void) const = 0;
	virtual Qt::ItemFlags flags(void) const = 0;

	// double dispath function
	virtual QGraphicsItem* add(QGraphicsScene* graphicsScene) = 0;
};
