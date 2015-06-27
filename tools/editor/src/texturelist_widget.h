
#pragma once

#include <QDockWidget>
namespace Ui {class TextureListWidget;}

class TextureListModel;

// -----------------------------------
//  TextureListWidget
// -----------------------------------
class TextureListWidget : public QDockWidget
{
	Q_OBJECT
public:
	TextureListWidget(QWidget *parent = Q_NULLPTR);
	~TextureListWidget();

private:
	Ui::TextureListWidget *ui_;
	TextureListModel* textureListModel_;
};

