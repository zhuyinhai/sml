#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Composition;
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
    Ui::MainWindow *ui_;
    Composition* composition_;
    TimelineDelegate* delegate_;
};

#endif // MAINWINDOW_H
