#include "itemlist_widget.h"
#include "ui_itemlist_widget.h"
#include "itemlist_model.h"

// -----------------------------------
//  ItemListWidget
// -----------------------------------
ItemListWidget::ItemListWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = new Ui::ItemListWidget();
	ui_->setupUi(this);

	itemListModel_ = new ItemListModel(this);
	ui_->treeView->setModel(itemListModel_);
	ui_->treeView->setSelectionModel(new QItemSelectionModel(itemListModel_));
}

ItemListWidget::~ItemListWidget()
{
	::SafeDelete(ui_);
}

ItemListView* ItemListWidget::getItemListView(void)
{
	return ui_->treeView;
}
