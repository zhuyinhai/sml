
#pragma once

#include <QTreeView>

// -----------------------------------
//  ItemListView
// -----------------------------------
class ItemListView : public QTreeView
{
	Q_OBJECT

public:
	ItemListView(QWidget *parent = Q_NULLPTR);
	virtual ~ItemListView(void);

	void dragEnterEvent(QDragEnterEvent *) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent* e) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *) Q_DECL_OVERRIDE;

public slots:
	void showContextMenu(const QPoint& pos);
};

