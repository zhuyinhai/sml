
#pragma once

#include <QDockWidget>

#include "item/item_handle.h"

namespace Ui {class KeyframeWidget;}
class KeyframeModel;

// -----------------------------------
//  KeyframeWidget
// -----------------------------------
class KeyframeWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit KeyframeWidget(QWidget *parent = 0);
	virtual ~KeyframeWidget(void);

public slots:
	void onItemSelected(ItemHandle hItem);

private:
	Ui::KeyframeWidget* ui_;
};

