#pragma once

#include <QMainWindow>

namespace Ui{ class MainWindow; }
class ItemListWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow(void);

private slots:
	void actionNewTriggered(void);
	void actionOpenTriggered(void);
	void actionSaveTriggered(void);

private:
	Ui::MainWindow* ui_;
	ItemListWidget* itemListWidget_;
};

