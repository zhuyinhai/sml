#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QMetaClassInfo>
#include "timelinedelegate.h"
#include "timelineitem.h"

class Layer : public QList<QStandardItem*>
{
public:
    Layer(const QString& text)
    {
        initialize(text);
    }
    virtual ~Layer(void) = default;

private:
    void initialize(const QString& text)
    {
        auto root = new QStandardItem(text);
        auto dummy = new QStandardItem();
        dummy->setEditable(false);
        auto dummy2 = new QStandardItem();
        dummy2->setEditable(false);
        *this << root << dummy << dummy2;

        auto addParam = [root, this](const char* name, std::initializer_list<const char*> list ){
            auto param = new QStandardItem(name);
            param->setEditable(false);
            for( auto name : list )
            {
                auto nameItem = new QStandardItem(name);
                nameItem->setEditable(false);
                auto valueItem = new QStandardItem("0.0");
                auto timelineItem = new TimelineItem(this);
                param->appendRow(QList<QStandardItem*>() << nameItem << valueItem << timelineItem);
            }
            root->appendRow(QList<QStandardItem*>() << param );
        };

        addParam( "anchor", {"x","y"} );
        addParam( "position", {"x","y"} );
        addParam( "scale", {"x","y"} );
        addParam( "rotate", {"x", "y", "z"} );
        addParam( "color", {"r","g","b","a"} );
    }
};


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
    qRegisterMetaType<KeyframeList*>("KeyframeList");

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
