
#pragma once

#include <QTreeView>

// -----------------------------------
//  TextureListView
// -----------------------------------
class TextureListView : public QTreeView
{
	Q_OBJECT

public:
	TextureListView(QWidget *parent = Q_NULLPTR);
	virtual ~TextureListView(void);

	// void dragEnterEvent(QDragEnterEvent *) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent* e) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *) Q_DECL_OVERRIDE;

public slots:
	void showContextMenu(const QPoint& pos);
};

