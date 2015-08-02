
#include "item/item_image.h"

#include <QIcon>
#include <QGraphicsPixmapItem>


// -----------------------------------
//  ItemImage
// -----------------------------------
ItemImage::ItemImage(const QUrl& url)
	: url_(url)
	, pixmapItem_(nullptr)
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

QGraphicsItem* ItemImage::getGraphicsItem(void)
{
	return new QGraphicsPixmapItem( QPixmap(url_.toLocalFile()) );
}
