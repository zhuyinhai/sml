
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>

#include "texturelist_view.h"


// -----------------------------------
//  TextureListView
// -----------------------------------
TextureListView::TextureListView(QWidget *parent)
	: QTreeView(parent)
{
	setAcceptDrops(true);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(showContextMenu(const QPoint&)));
}

TextureListView::~TextureListView(void)
{}


void TextureListView::dragEnterEvent(QDragEnterEvent* e)
{
	e->accept();
}

void TextureListView::dragMoveEvent(QDragMoveEvent * e)
{
	e->setDropAction(Qt::LinkAction);
	e->accept();
}

void TextureListView::dropEvent(QDropEvent *)
{}

void TextureListView::showContextMenu(const QPoint& pos)
{
	QMenu menu;
	QAction* actionItem1 = menu.addAction("Menu Item 1");
	QAction* actionItem2 = menu.addAction("Menu Item 2");

	QAction* selected = menu.exec(mapToGlobal(pos));
	if(selected == actionItem1)
	{
		qDebug() << "item1";
	}
	else if(selected == actionItem2)
	{
		qDebug() << "item2";
	}
	else
	{
		// nothing was chosen
	}
}
