
#pragma once

#include <QDockWidget>
namespace Ui {class KeyframeWidget;};

// -----------------------------------
//  KeyframeWidget
// -----------------------------------
class KeyframeWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit KeyframeWidget(QWidget *parent = 0);
	virtual ~KeyframeWidget(void);

private:
	Ui::KeyframeWidget* ui_;
};

