#include "itemlist_widget.h"
#include "ui_itemlist_widget.h"
#include "itemlist_model.h"

// -----------------------------------
//  ItemListWidget
// -----------------------------------
ItemListWidget::ItemListWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui_ = NEW Ui::ItemListWidget();
	ui_->setupUi(this);

	itemListModel_ = NEW ItemListModel(this);
	ui_->treeView->setModel(itemListModel_);
	ui_->treeView->setSelectionModel(NEW QItemSelectionModel(itemListModel_));
}

ItemListWidget::~ItemListWidget()
{
	::SafeDelete(ui_);
}

