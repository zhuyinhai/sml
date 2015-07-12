
#pragma once

#include <QGraphicsView>

// -----------------------------------
//  ItemView
// -----------------------------------
class ItemView : public QGraphicsView
{
public:
	explicit ItemView(QWidget *parent = nullptr);
	virtual ~ItemView(void);

	void dragMoveEvent(QDragMoveEvent* e) override;
	void dropEvent(QDropEvent* e) override;


};

