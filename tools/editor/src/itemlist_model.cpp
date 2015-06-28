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
{}

ItemListModel::~ItemListModel(void)
{}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
	if( index.isValid() && Qt::DecorationRole == role )
	{
		if( auto item = itemFromIndex(index) )
		{
			auto data = item->data().value<ItemHandle>();
			if( !data.isNull() )
			{
				return data->getDecorationRole();
			}
		}
	}
	return QStandardItemModel::data(index, role);
}

Qt::ItemFlags ItemListModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags;
	if(index.isValid())
	{
		flags = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
	{
		flags = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
	}
	return flags;
}

Qt::DropActions ItemListModel::supportedDropActions(void) const
{
	return Qt::MoveAction;
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

