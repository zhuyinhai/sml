
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>

#include "main_window.h"
#include "ui_main_window.h"

#include "texturelist_widget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui_ = new Ui::MainWindow();

	ui_->setupUi(this);

	connect(ui_->actionNew, SIGNAL(triggered()), this, SLOT(actionNewTriggered()));
	connect(ui_->actionOpen, SIGNAL(triggered()), this, SLOT(actionOpenTriggered()));
	connect(ui_->actionSave, SIGNAL(triggered()), this, SLOT(actionSaveTriggered()));


	textureListWidget_ = new TextureListWidget();
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, textureListWidget_);
}

MainWindow::~MainWindow()
{

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
