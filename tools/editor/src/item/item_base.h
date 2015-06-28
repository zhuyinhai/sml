#pragma once

#include <QMetaType>
#include <QIcon>
#include <QSharedPointer>

// -----------------------------------
//  ItemType
// -----------------------------------
enum class ItemType
{
	FOLDER,
	IMAGE,
	COMPOSITION,
	PLANE
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
};
