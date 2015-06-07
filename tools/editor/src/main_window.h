#pragma once

#include <QMainWindow>

namespace Ui{ class MainWindow; }
class TextureListWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void actionNewTriggered(void);
	void actionOpenTriggered(void);
	void actionSaveTriggered(void);

private:
	Ui::MainWindow* ui_;
	TextureListWidget* textureListWidget_;
};

