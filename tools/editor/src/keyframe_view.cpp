
#include <QDebug>

#include "keyframe_view.h"
#include "item/item_base.h"
#include "item/item_composition.h"
#include "keyframe_model.h"

// -----------------------------------
//  KeyframeView
// -----------------------------------
KeyframeView::KeyframeView(QWidget* parent)
	: QTreeView(parent)
{}

KeyframeView::~KeyframeView(void)
{}

void KeyframeView::onItemSelected(ItemHandle hItem)
{
	if(!hItem.isNull() && ItemType::COMPOSITION == hItem->getItemType())
	{
		ItemComposition* composition = static_cast<ItemComposition*>(hItem.get());
		setModel( composition->getKeyframeModel() );
		show();
	}
	qDebug() << hItem->getName();
}