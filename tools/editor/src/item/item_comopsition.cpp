
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


QGraphicsItem* ItemComposition::add(QGraphicsScene* graphicsScene)
{
	if(!graphicsScene)
	{
		return nullptr;
	}
	return graphicsScene->addRect( QRectF() );
}


QGraphicsScene* ItemComposition::getGraphicsScene(void)
{
	if(!graphicsScene_)
	{
		graphicsScene_ = new QGraphicsScene();
	}

	return graphicsScene_;
}

void ItemComposition::addItem(ItemHandle hItem)
{
	if( hItem.isNull() )
	{
		return;
	}

	Data data = {
		hItem,
		QPointF(),
		QPointF(),
		QSizeF(),
		qreal(),
		QColor()
	};

	itemList_.append(data);

	if(!graphicsScene_)
	{
		return;
	}

}




