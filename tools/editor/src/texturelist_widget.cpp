#include "texturelist_widget.h"
#include "ui_texturelist_widget.h"
#include "texturelist_model.h"
#include "texturelist_item.h"

TextureListWidget::TextureListWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = new Ui::TextureListWidget();
	ui_->setupUi(this);

	textureListModel_ = new TextureListModel(this);

	textureListModel_->newFolder("test1");
	auto test2 = textureListModel_->newFolder("test2");
	auto test3 = new TextureFolder();
	test3->setName("test3");
	test2->addItem(test3);

	ui_->treeView->setModel(textureListModel_);
}

TextureListWidget::~TextureListWidget()
{
	delete ui_;
}

