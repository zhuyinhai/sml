
#include "item_view.h"

#include <QDebug>
#include <QDropEvent>
#include <QGraphicsItem>

#include "itemlist_view.h"
#include "itemlist_model.h"
#include "item/item_handle.h"
#include "item/item_base.h"
#include "item/item_composition.h"

// -----------------------------------
//  ItemView
// -----------------------------------
ItemView::ItemView(QWidget* parent)
	: QGraphicsView(parent)
	, hItem_()
	, composition_(nullptr)
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
			if(composition_)
			{
				composition_->addItem(mdl->getItem(listView->currentIndex()));
				e->ignore();
				return;
			}
		}
	}
	QGraphicsView::dropEvent(e);
}

void ItemView::onItemSelected(ItemHandle hItem)
{
	if(hItem.isNull())
	{
		return;
	}

	hItem_ = hItem;
	if( ItemType::COMPOSITION == hItem->getItemType() )
	{
		ItemComposition* composition = static_cast<ItemComposition*>(hItem.get());
		setScene(composition->getGraphicsScene());
		composition_ = composition;
	}

	qDebug() << "item selected";
}

