#pragma once

#include <QMainWindow>

namespace Ui{ class MainWindow; }
class ItemListWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void actionNewTriggered(void);
	void actionOpenTriggered(void);
	void actionSaveTriggered(void);

private:
	Ui::MainWindow* ui_;
	ItemListWidget* itemListWidget_;
};

