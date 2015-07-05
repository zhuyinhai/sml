
#pragma once

#include <QTreeView>

// -----------------------------------
//  ItemListView
// -----------------------------------
class ItemListView : public QTreeView
{
	Q_OBJECT

public:
	explicit ItemListView(QWidget *parent = nullptr);
	virtual ~ItemListView(void);

	void dragEnterEvent(QDragEnterEvent *) override;
	void dragMoveEvent(QDragMoveEvent* e) override;
	void dropEvent(QDropEvent *) override;

public slots:
	void showContextMenu(const QPoint& pos);
};

