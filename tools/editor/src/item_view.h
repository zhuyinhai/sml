
#pragma once

#include <QGraphicsView>
#include "item/item_handle.h"

class ItemComposition;

// -----------------------------------
//  ItemView
// -----------------------------------
class ItemView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit ItemView(QWidget *parent = nullptr);
	virtual ~ItemView(void);

	void dragMoveEvent(QDragMoveEvent* e) override;
	void dropEvent(QDropEvent* e) override;

public slots:
	void onItemSelected(ItemHandle hItem);

private:
	ItemHandle hItem_;
	ItemComposition* composition_;
};

