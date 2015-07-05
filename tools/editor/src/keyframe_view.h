
#pragma once

#include <QTreeView>

// -----------------------------------
//  KeyframeView
// -----------------------------------
class KeyframeView : public QTreeView
{
	Q_OBJECT
public:
	explicit KeyframeView(QWidget *parent = nullptr);
	virtual ~KeyframeView(void);

};

