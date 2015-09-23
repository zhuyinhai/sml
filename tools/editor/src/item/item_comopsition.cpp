
#include "item/item_composition.h"

#include <QApplication>
#include <QStyle>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "keyframe_model.h"

// -----------------------------------
//  ItemComposition
// -----------------------------------
ItemComposition::ItemComposition(void)
	: graphicsScene_(nullptr)
	, keyframeModel_(nullptr)
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

	QString name = hItem->getName().split(".", QString::SkipEmptyParts)[0];
	


	bool isNameDupulicated = false;
	do
	{
		for(const auto& layer : layers_)
		{
			if( name==layer.name )
			{
				isNameDupulicated = true;
				break;
			}
		}

		if(isNameDupulicated)
		{
			auto strList = name.split(QRegExp("[0-9]+"));
			qDebug() << strList;
			isNameDupulicated = false;
		}
	}while(isNameDupulicated);


	Layer layer = {
		hItem,
		name,
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

	if(keyframeModel_)
	{
		keyframeModel_->appendRow(new QStandardItem(layer.name));
	}
}

KeyframeModel* ItemComposition::getKeyframeModel(void)
{
	if(!keyframeModel_)
	{
		keyframeModel_ = new KeyframeModel();

		for(auto& layer : layers_)
		{
			keyframeModel_->appendRow( new QStandardItem("test") );
		}

	}
	return keyframeModel_;
}


