#include "texturelist_widget.h"
#include "ui_texturelist_widget.h"

TextureListWidget::TextureListWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = new Ui::TextureListWidget();
	ui_->setupUi(this);
}

TextureListWidget::~TextureListWidget()
{
	delete ui_;
}

