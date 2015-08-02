
#include <QDebug>

#include "keyframe_view.h"
#include "item/item_base.h"

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
	qDebug() << hItem->getName();
}