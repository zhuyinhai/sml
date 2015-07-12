
#include "item_view.h"

#include <QDebug>
#include <QDropEvent>
#include <QGraphicsItem>

#include "itemlist_view.h"
#include "itemlist_model.h"
#include "item/item_handle.h"
#include "item/item_base.h"

// -----------------------------------
//  ItemView
// -----------------------------------
ItemView::ItemView(QWidget* parent)
	: QGraphicsView(parent)
{}

ItemView::~ItemView(void)
{}

void ItemView::dragMoveEvent(QDragMoveEvent* e)
{
	if(ItemListView* listView = qobject_cast<ItemListView*>(e->source()))
	{
		if(ItemListModel* mdl = qobject_cast<ItemListModel*>(listView->model()))
		{
			ItemHandle hItem = mdl->getItem(listView->currentIndex());
			if(!hItem.isNull())
			{
				ItemType type = hItem->getItemType();
				if( type != ItemType::FOLDER )
				{
					e->accept();
					return;
				}
			}
		}
	}
	QGraphicsView::dragMoveEvent(e);
}

void ItemView::dropEvent(QDropEvent* e)
{
	
	if(ItemListView* listView = qobject_cast<ItemListView*>(e->source()))
	{
		if(ItemListModel* mdl = qobject_cast<ItemListModel*>(listView->model()))
		{
			ItemHandle hItem = mdl->getItem(listView->currentIndex());
			if(!hItem.isNull())
			{
				QGraphicsItem* item = hItem->add(scene());
				item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
				e->ignore();
				return;
			}
		}
	}
	QGraphicsView::dropEvent(e);
}

