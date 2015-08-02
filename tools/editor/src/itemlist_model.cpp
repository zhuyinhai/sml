#include <QIcon>
#include <QApplication>
#include <QStyle>
#include <QDebug>

#include "item/item_base.h"
#include "item/item_handle.h"

#include "itemlist_model.h"

// -----------------------------------
//  ItemListModel
// -----------------------------------
ItemListModel::ItemListModel(QObject* parent)
	: QStandardItemModel(parent)
{
	connect(this, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onItemChangedCallback(QStandardItem*)));
}

ItemListModel::~ItemListModel(void)
{}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
	if( index.isValid() && Qt::DecorationRole == role )
	{
		ItemHandle hItem = getItem(index);
		if(!hItem.isNull())
		{
			return hItem->getDecorationRole();
		}
	}
	return QStandardItemModel::data(index, role);
}

Qt::ItemFlags ItemListModel::flags(const QModelIndex& index) const
{
	ItemHandle hItem = getItem(index);
	if(hItem.isNull())
	{
		return Qt::NoItemFlags;
	}
	return hItem->flags();
}

bool ItemListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
	const QModelIndex &destinationParent, int destinationChild)
{
	if(QStandardItem* dest = itemFromIndex(destinationParent))
	{	
		if(QStandardItem* srcParentItem = itemFromIndex(sourceParent))
		{
			for(int i = 0; i<count; ++i)
			{
				dest->insertRow(destinationChild, srcParentItem->takeRow(sourceRow+i));
			}
		}
		else
		{
			for(int i = 0; i<count; ++i)
			{
				dest->insertRow(destinationChild, takeRow(sourceRow + i));
			}
		}
	}

	return true;
}


ItemHandle ItemListModel::getItem(const QModelIndex& index) const
{
	if( !index.isValid() )
	{
		return ItemHandle();
	}

	if(auto item = itemFromIndex(index))
	{
		return item->data().value<ItemHandle>();
	}

	return ItemHandle();
}

void ItemListModel::onItemChangedCallback(QStandardItem* item)
{
	ItemHandle hItem = item->data().value<ItemHandle>();
	if(hItem.isNull())
	{
		return;
	}
	QString name = item->data(Qt::DisplayRole).toString();
	hItem->setName(name);
	qDebug() << name;
}