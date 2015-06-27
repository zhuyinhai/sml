#include "texturelist_widget.h"
#include "ui_texturelist_widget.h"
#include "texturelist_model.h"

// -----------------------------------
//  TextureListWidget
// -----------------------------------
TextureListWidget::TextureListWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = new Ui::TextureListWidget();
	ui_->setupUi(this);

	textureListModel_ = new TextureListModel(this);
	ui_->treeView->setModel(textureListModel_);
}

TextureListWidget::~TextureListWidget()
{
	delete ui_;
}

