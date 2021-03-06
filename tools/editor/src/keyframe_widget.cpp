#include "keyframe_widget.h"
#include "ui_keyframe_widget.h"

#include "keyframe_model.h"

// -----------------------------------
//  KeyframeWidget
// -----------------------------------
KeyframeWidget::KeyframeWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = new Ui::KeyframeWidget();
	ui_->setupUi(this);
}

KeyframeWidget::~KeyframeWidget()
{
	SafeDelete(ui_);
}

void KeyframeWidget::onItemSelected(ItemHandle hItem)
{
	ui_->treeView->onItemSelected(hItem);
}

