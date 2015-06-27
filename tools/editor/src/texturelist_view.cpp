
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>

#include "texturelist_view.h"
#include "texturelist_model.h"

// -----------------------------------
//  TextureListView
// -----------------------------------
TextureListView::TextureListView(QWidget *parent)
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

TextureListView::~TextureListView(void)
{}

#if 0
void TextureListView::dragEnterEvent(QDragEnterEvent* e)
{
	e->acceptProposedAction();
}
#endif

void TextureListView::dragMoveEvent(QDragMoveEvent* e)
{
	QModelIndex destIndex = indexAt(e->pos());
	if(!destIndex.isValid())
	{
		QTreeView::dragMoveEvent(e);
		return;
	}
	if(auto mdl = qobject_cast<TextureListModel*>(model()))
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

void TextureListView::dropEvent(QDropEvent * e)
{
	QModelIndex droppedIndex = indexAt( e->pos() );

	if(!droppedIndex.isValid())
	{
		QTreeView::dropEvent(e);
		return;
	}

	if(auto mdl = qobject_cast<TextureListModel*>(model()))
	{
		for( auto index : selectedIndexes() )
		{
			mdl->moveRows( index.parent(), index.row(), 1, droppedIndex, 0 );
			break;
		}
	}
}


void TextureListView::showContextMenu(const QPoint& pos)
{
	QMenu menu;
	QAction* actionAddFolder = menu.addAction("Add Folder");

	QAction* selected = menu.exec(mapToGlobal(pos));
	if(selected == actionAddFolder)
	{
		if(TextureListModel* mdl = static_cast<TextureListModel*>(model()))
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
