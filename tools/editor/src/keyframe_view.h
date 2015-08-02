
#pragma once

#include <QTreeView>

#include "item/item_handle.h"

// -----------------------------------
//  KeyframeView
// -----------------------------------
class KeyframeView : public QTreeView
{
	Q_OBJECT
public:
	explicit KeyframeView(QWidget *parent = nullptr);
	virtual ~KeyframeView(void);

public slots:
	void onItemSelected(ItemHandle hItem);
};

