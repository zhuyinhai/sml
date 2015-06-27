#include <QIcon>
#include <QApplication>
#include <QStyle>
#include <QDebug>

#include "texturelist_model.h"

// -----------------------------------
//  TextureListModel
// -----------------------------------
TextureListModel::TextureListModel(QObject* parent)
	: QStandardItemModel(parent)
{}

TextureListModel::~TextureListModel(void)
{}

QVariant TextureListModel::data(const QModelIndex &index, int role) const
{
	if( index.isValid() && Qt::DecorationRole == role )
	{
		return QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon);
	}
	return QStandardItemModel::data(index, role);
}

Qt::ItemFlags TextureListModel::flags(const QModelIndex& index) const
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

Qt::DropActions TextureListModel::supportedDropActions(void) const
{
	return Qt::MoveAction;
}

bool TextureListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
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

