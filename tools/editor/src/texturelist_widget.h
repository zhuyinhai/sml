#ifndef TEXTURELIST_WIDGET_H
#define TEXTURELIST_WIDGET_H

#include <QDockWidget>
namespace Ui {class TextureListWidget;}

class TextureListWidget : public QDockWidget
{
	Q_OBJECT

public:
	TextureListWidget(QWidget *parent = 0);
	~TextureListWidget();

private:
	Ui::TextureListWidget *ui_;
};

#endif // TEXTURELIST_WIDGET_H
