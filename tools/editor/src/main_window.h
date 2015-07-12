#pragma once

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui{ class MainWindow; }
class ItemListWidget;
class KeyframeWidget;

// -----------------------------------
//  MainWindow
// -----------------------------------
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow(void);

private slots:
	void actionNewTriggered(void);
	void actionOpenTriggered(void);
	void actionSaveTriggered(void);

private:
	Ui::MainWindow* ui_;
	ItemListWidget* itemListWidget_;
	KeyframeWidget* keyframeWidget_;

	QGraphicsScene* graphicsScene_;
};

