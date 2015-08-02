#pragma once

#include <QVariant>
#include <QDebug>

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
	ItemBase(void);
	virtual ~ItemBase(void) = default;

	virtual QVariant getDecorationRole(void) const = 0;
	virtual ItemType getItemType(void) const = 0;
	virtual Qt::ItemFlags flags(void) const = 0;

	virtual QGraphicsItem* getGraphicsItem(void) = 0;

	void setName(const QString& name);
	const QString& getName(void) const;

private:
	QString name_;
};


// -- implement 

inline ItemBase::ItemBase(void)
{}

inline void ItemBase::setName(const QString& name)
{
	name_ = name;
}

inline const QString& ItemBase::getName(void) const
{
	return name_;
}
