
#include "texturelist_model.h"
#include "texturelist_item.h"

namespace
{
	inline TextureListItemBase* getItem(const QModelIndex& index)
	{
		return static_cast<TextureListItemBase*>(index.internalPointer());
	}
}


// -----------------------------------
//  TextureListModel
// -----------------------------------
TextureListModel::TextureListModel(QObject* parent)
	: QAbstractItemModel(parent)
	, root_( new TextureFolder() )
{}

TextureListModel::~TextureListModel(void)
{
	delete root_;
}


QModelIndex TextureListModel::index(int row, int column, const QModelIndex &parent) const
{
	if(!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	TextureListItemBase* parentItem = nullptr;

	if(parent.isValid())
	{
		parentItem = getItem(parent);
	}
	else
	{
		parentItem = root_;
	}

	if( TextureListItemBase* childItem = parentItem->getChild(row) )
	{
		return createIndex(row, column, childItem);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex TextureListModel::parent(const QModelIndex &child) const
{
	if(!child.isValid())
	{
		return QModelIndex();
	}

	if(TextureListItemBase* childItem = getItem(child))
	{
		if( TextureListItemBase* parentItem = childItem->getParent() )
		{
			if(TextureListItemBase* parentParentItem = parentItem->getParent())
			{
				return createIndex( parentParentItem->getRow(parentItem), 0, parentItem );
			}
		}
	}
	return QModelIndex();
}

int TextureListModel::rowCount(const QModelIndex &parent) const
{
	TextureListItemBase* parentItem = (parent.isValid()) ? getItem(parent) : root_;
	return parentItem->getChildCount();
}

int TextureListModel::columnCount(const QModelIndex &parent) const
{
	if(parent.isValid())
	{
		return getItem(parent)->getColomnCount();
	}
	else
	{
		return root_->getColomnCount();
	}
}

QVariant TextureListModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}
	if(role != Qt::DisplayRole)
	{
		return QVariant();
	}
	return getItem(index)->getColumn(index.column());
}


Qt::ItemFlags TextureListModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
	if(index.isValid())
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
	else
		return Qt::ItemIsDropEnabled | defaultFlags;
}

TextureFolder* TextureListModel::newFolder(const QString& name)
{
	TextureFolder* folder = new TextureFolder();
	folder->setName(name);
	root_->addItem(folder);
	return folder;
}