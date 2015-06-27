
#pragma once

#include <QDockWidget>
namespace Ui {class ItemListWidget;}

class ItemListModel;

// -----------------------------------
//  ItemListWidget
// -----------------------------------
class ItemListWidget : public QDockWidget
{
	Q_OBJECT
public:
	ItemListWidget(QWidget *parent = Q_NULLPTR);
	~ItemListWidget();

private:
	Ui::ItemListWidget *ui_;
	ItemListModel* itemListModel_;
};

