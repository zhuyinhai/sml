#pragma once

#include <QMainWindow>
#include <QGraphicsScene>

#include "item/item_handle.h"

namespace Ui{ class MainWindow; }
class ItemListWidget;
class KeyframeWidget;


// -----------------------------------
//  MainWindow
// -----------------------------------
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow(void);

private slots:
	void actionNewTriggered(void);
	void actionOpenTriggered(void);
	void actionSaveTriggered(void);

	void onItemSelected(ItemHandle hItem);

private:
	Ui::MainWindow* ui_;
	ItemListWidget* itemListWidget_;
	KeyframeWidget* keyframeWidget_;
};

