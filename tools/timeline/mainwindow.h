#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



class QStandardItem;
class QStandardItemModel;
class TimelineDelegate;
class Layer;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    TimelineDelegate* delegate;
    Layer* layer;
};

#endif // MAINWINDOW_H
