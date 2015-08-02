
#pragma once

#include <QDockWidget>
namespace Ui {class ItemListWidget;}

class ItemListModel;
class ItemListView;

// -----------------------------------
//  ItemListWidget
// -----------------------------------
class ItemListWidget : public QDockWidget
{
	Q_OBJECT
public:
	explicit ItemListWidget(QWidget *parent = nullptr);
	~ItemListWidget(void);

	ItemListView* getItemListView(void);

private:
	Ui::ItemListWidget *ui_;
	ItemListModel* itemListModel_;
};

