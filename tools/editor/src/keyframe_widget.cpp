#include "keyframe_widget.h"
#include "ui_keyframe_widget.h"

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

