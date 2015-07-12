
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

	void dragEnterEvent(QDragEnterEvent* e) override;
	void dragMoveEvent(QDragMoveEvent* e) override;
	void dropEvent(QDropEvent *) override;

public slots:
	void showContextMenu(const QPoint& pos);
	void onDoubleClicked(const QModelIndex &index);
};

Q_DECLARE_METATYPE(ItemListView*);