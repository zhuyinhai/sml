
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>
#include <QImageReader>

#include "item/item_folder.h"
#include "item/item_image.h"
#include "item/item_handle.h"

#include "itemlist_view.h"
#include "itemlist_model.h"


// -----------------------------------
//  ItemListView
// -----------------------------------
ItemListView::ItemListView(QWidget *parent)
	: QTreeView(parent)
{
	setAcceptDrops(true);
	setDragEnabled(true);
	setDragDropOverwriteMode(false);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DragDrop);
	setDefaultDropAction(Qt::MoveAction);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(showContextMenu(const QPoint&)));
}

ItemListView::~ItemListView(void)
{}


void ItemListView::dragEnterEvent(QDragEnterEvent* e)
{
	if(e->mimeData()->hasUrls())
	{
		e->acceptProposedAction();
		return;
	}

	QTreeView::dragEnterEvent(e);
}


void ItemListView::dragMoveEvent(QDragMoveEvent* e)
{
	// internal move 
	if( this == e->source() )
	{
		QModelIndex destIndex = indexAt(e->pos());
		if(!destIndex.isValid())
		{
			QTreeView::dragMoveEvent(e);
			return;
		}
		if(auto mdl = static_cast<ItemListModel*>(model()))
		{
			const QStandardItem* destItem = mdl->itemFromIndex(destIndex);
			if( nullptr==destItem )
			{
				QTreeView::dragMoveEvent(e);
				return;
			}
			ItemHandle handle = destItem->data().value<ItemHandle>();
			if( handle.isNull() )
			{
				QTreeView::dragMoveEvent(e);
				return;
			}
			if( ItemType::FOLDER != handle->getItemType() )
			{
				e->ignore();
				return;
			}

			for(auto& index : selectedIndexes())
			{
				const QStandardItem* srcItem = mdl->itemFromIndex(index);
				const QStandardItem* checkItem = destItem;
				do
				{
					if(srcItem == checkItem)
					{
						e->ignore();
						return;
					}
				} while(checkItem = checkItem->parent());
			}
		}
		e->acceptProposedAction();
	}
	else if(const QMimeData* mimeData = e->mimeData())
	{
		if(e->mimeData()->hasUrls())
		{
			QModelIndex destIndex = indexAt(e->pos());
			if(destIndex.isValid())
			{
				if(auto mdl = static_cast<ItemListModel*>(model()))
				{
					if( const QStandardItem* destItem = mdl->itemFromIndex(destIndex) )
					{
						ItemHandle handle = destItem->data().value<ItemHandle>();
						if(!handle.isNull())
						{
							if( ItemType::FOLDER != handle->getItemType() )
							{
								e->ignore();
								return;
							}
						}
					}
				}
			}

			e->accept();
		}
		else
		{
			e->ignore();
		}
	}
}

void ItemListView::dropEvent(QDropEvent * e)
{
	QModelIndex droppedIndex = indexAt( e->pos() );

	if(this == e->source())
	{
		if(!droppedIndex.isValid())
		{
			QTreeView::dropEvent(e);
			return;
		}

		if(auto mdl = static_cast<ItemListModel*>(model()))
		{
			for( auto index : selectedIndexes() )
			{
				mdl->moveRows( index.parent(), index.row(), 1, droppedIndex, 0 );
				break;
			}
		}
	}
	else if(const QMimeData* mimeData = e->mimeData())
	{
		if(auto mdl = static_cast<ItemListModel*>(model()))
		{
			for(auto& url : mimeData->urls())
			{
				if( !url.isLocalFile() )
				{
					continue;
				}
				QImageReader reader(url.toLocalFile());
				if( !reader.canRead() )
				{
					continue;
				}

				QList<QStandardItem*> list;

				auto item = NEW QStandardItem(url.fileName());
				item->setData(QVariant::fromValue<ItemHandle>(ItemStore::create<ItemImage>(url)));
				list.append(item);
				list.append(NEW QStandardItem(url.toString()));

				if(auto parent = mdl->itemFromIndex(droppedIndex))
				{
					parent->insertRow(parent->rowCount(), list);
					expand(mdl->indexFromItem(parent));
				}
				else
				{
					mdl->appendRow(list);
				}
			}
		}
	}
}


void ItemListView::showContextMenu(const QPoint& pos)
{
	QMenu menu;
	QAction* actionAddFolder = menu.addAction("Add Folder");

	QAction* selected = menu.exec(mapToGlobal(pos));
	if(selected == actionAddFolder)
	{
		if(auto mdl = static_cast<ItemListModel*>(model()))
		{
			QStandardItem* item = NEW QStandardItem("folder");
			item->setData(QVariant::fromValue<ItemHandle>(ItemStore::create<ItemFolder>()));
			QModelIndex index = indexAt(pos);
			if( auto parent = mdl->itemFromIndex(index) )
			{
				parent->insertRow( parent->rowCount(), item );
				expand(mdl->indexFromItem(parent));
			}
			else
			{
				mdl->appendRow(item);
			}

			edit(mdl->indexFromItem(item));
		}
	}
	else
	{
		// nothing was chosen
	}
}
