
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>

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
	setDragDropMode(QAbstractItemView::InternalMove);
	setDefaultDropAction(Qt::MoveAction);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(showContextMenu(const QPoint&)));

	setSelectionModel( new QItemSelectionModel(model(), this) );
}

ItemListView::~ItemListView(void)
{}

#if 0
void ItemListView::dragEnterEvent(QDragEnterEvent* e)
{
	e->acceptProposedAction();
}
#endif

void ItemListView::dragMoveEvent(QDragMoveEvent* e)
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
		for(auto index : selectedIndexes())
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

void ItemListView::dropEvent(QDropEvent * e)
{
	QModelIndex droppedIndex = indexAt( e->pos() );

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


void ItemListView::showContextMenu(const QPoint& pos)
{
	QMenu menu;
	QAction* actionAddFolder = menu.addAction("Add Folder");

	QAction* selected = menu.exec(mapToGlobal(pos));
	if(selected == actionAddFolder)
	{
		if(auto mdl = static_cast<ItemListModel*>(model()))
		{
			QStandardItem* item = new QStandardItem("folder");
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
