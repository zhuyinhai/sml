
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
	explicit ItemListWidget(QWidget *parent = nullptr);
	~ItemListWidget(void);

private:
	Ui::ItemListWidget *ui_;
	ItemListModel* itemListModel_;
};

