
#include "item/item_composition.h"

#include <QApplication>
#include <QStyle>
#include <QGraphicsScene>
#include <QGraphicsItem>

// -----------------------------------
//  ItemComposition
// -----------------------------------
ItemComposition::ItemComposition(void)
	: graphicsScene_(nullptr)
{}

ItemComposition::~ItemComposition(void)
{
	::SafeDelete(graphicsScene_);
}

QVariant ItemComposition::getDecorationRole(void) const
{
	return QApplication::style()->standardIcon(QStyle::SP_FileIcon);
}

ItemType ItemComposition::getItemType(void) const
{
	return ItemType::COMPOSITION;
}

Qt::ItemFlags ItemComposition::flags(void) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;
}


QGraphicsItem* ItemComposition::getGraphicsItem(void)
{
	return nullptr;
}


QGraphicsScene* ItemComposition::getGraphicsScene(void)
{
	if(!graphicsScene_)
	{
		graphicsScene_ = new QGraphicsScene();
		graphicsScene_->addLine(QLineF(QPointF(0.0, 0.0), QPointF(100.0, 0.0)));
		graphicsScene_->addLine(QLineF(QPointF(0.0, 0.0), QPointF(.0, 100.0)));
	}

	return graphicsScene_;
}

void ItemComposition::addItem(ItemHandle hItem)
{
	if( hItem.isNull() )
	{
		return;
	}

	QGraphicsItem* item = hItem->getGraphicsItem();
	if(!item)
	{
		return;
	}
	item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

	Layer layer = {
		hItem,
		QPointF(),
		QPointF(),
		QSizeF(),
		qreal(),
		QColor(),
		item
	};

	layers_.append(layer);

	QGraphicsScene* scene = getGraphicsScene();
	scene->addItem(item);
}




