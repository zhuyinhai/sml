
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QMetaClassInfo>
#include <QPainter>

#include "timelinedelegate.h"
#include "timelineitem.h"
#include "layer.h"
#include "composition.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    composition_(new Composition),
    delegate_(new TimelineDelegate)
{
    ui_->setupUi(this);

    composition_->setDuration(10.f);
    composition_->newLayer<Layer,const QString&>("test");
    composition_->newLayer<Layer,const QString&>("test2");

    ui_->treeView->setModel(composition_);
    ui_->treeView->setItemDelegate(delegate_);

    ui_->treeView->header()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui_->treeView->header()->resizeSection(2, 1000);

    ui_->treeView->init();


}

MainWindow::~MainWindow()
{
    delete delegate_;
    delete composition_;
    delete ui_;
}
