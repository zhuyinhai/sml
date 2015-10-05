
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QMetaClassInfo>
#include "timelinedelegate.h"
#include "timelineitem.h"
#include "layer.h"

class TimelineModel : public QStandardItemModel
{
public:
    TimelineModel(void)
    {
        initalize();
    }
    virtual ~TimelineModel(void) = default;
private:
    void initalize(void)
    {
        QStringList headerLabels = { "layer", "value", "timeline" };
        setHorizontalHeaderLabels( headerLabels );
    }
};




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new TimelineModel),
    delegate(new TimelineDelegate),
    layer(new Layer("test"))
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
    ui->treeView->setItemDelegate(delegate);
    model->appendRow(*layer);
}

MainWindow::~MainWindow()
{
    delete layer;
    delete delegate;
    delete model;
    delete ui;
}
