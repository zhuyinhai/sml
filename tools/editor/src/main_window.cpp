
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>

#include <QGraphicsItem>

#include "main_window.h"
#include "ui_main_window.h"

#include "itemlist_widget.h"
#include "keyframe_widget.h"
#include "itemlist_view.h"
#include "item_view.h"
#include "item/item_base.h"

// -----------------------------------
//  MainWindow
// -----------------------------------
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui_ = new Ui::MainWindow();

	ui_->setupUi(this);

	connect(ui_->actionNew, SIGNAL(triggered()), this, SLOT(actionNewTriggered()));
	connect(ui_->actionOpen, SIGNAL(triggered()), this, SLOT(actionOpenTriggered()));
	connect(ui_->actionSave, SIGNAL(triggered()), this, SLOT(actionSaveTriggered()));

	// -- 
	itemListWidget_ = new ItemListWidget();
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, itemListWidget_);

	// --
	keyframeWidget_ = new KeyframeWidget();
	addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, keyframeWidget_);

	connect(itemListWidget_->getItemListView(), SIGNAL(onItemSelected(ItemHandle)),
		ui_->graphicsView, SLOT(onItemSelected(ItemHandle)));

	connect(itemListWidget_->getItemListView(), SIGNAL(onItemSelected(ItemHandle)),
		this, SLOT(onItemSelected(ItemHandle)));

	connect(itemListWidget_->getItemListView(), SIGNAL(onItemSelected(ItemHandle)),
		keyframeWidget_, SLOT(onItemSelected(ItemHandle)));

}

MainWindow::~MainWindow()
{
	// 
	::SafeDelete(ui_);
}

void MainWindow::actionNewTriggered(void)
{}

void MainWindow::actionOpenTriggered(void)
{
	QString filePath = QFileDialog::getOpenFileName(this,
		tr("Open XML"), QDir::currentPath(), tr("XML Files (*.xml)"));

	if(filePath.isEmpty())
	{
		qDebug() << "failed to open file";
		return;
	}

	QFile file(filePath);
	file.open(QFile::ReadOnly | QFile::Text);

	file.close();
}

void MainWindow::actionSaveTriggered(void)
{
	QString filePath = QFileDialog::getSaveFileName(this,
		tr("Save XML"), QDir::currentPath(), tr("XML Files (*.xml)"));

	if(filePath.isEmpty())
	{
		qDebug() << "failed to open file";
		return;
	}

	QDomDocument doc("MyML");
	doc.appendChild( doc.createElement("MyML") );

	QString xml = doc.toString();

	QFile file(filePath);
	file.open(QFile::WriteOnly | QFile::Text);

	QTextStream out(&file);
	out << xml;
	
	file.close();
}


void MainWindow::onItemSelected(ItemHandle hItem)
{
	ui_->label->setText( hItem->getName() );
}