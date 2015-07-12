
#include "item/item_image.h"

#include <QIcon>
#include <QGraphicsScene>
#include <QGraphicsItem>


// -----------------------------------
//  ItemImage
// -----------------------------------
ItemImage::ItemImage(const QUrl& url)
	: url_(url)
{}


QVariant ItemImage::getDecorationRole(void) const
{
	return QIcon(url_.toLocalFile());
}

ItemType ItemImage::getItemType(void) const
{
	return ItemType::IMAGE;
}

Qt::ItemFlags ItemImage::flags(void) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QGraphicsItem* ItemImage::add(QGraphicsScene* graphicsScene)
{
	if(!graphicsScene)
	{
		return nullptr;
	}
	return graphicsScene->addPixmap(QPixmap(url_.toLocalFile()));
}
