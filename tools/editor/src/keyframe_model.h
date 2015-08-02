
#pragma once

#include <QStandardItemModel>

// -----------------------------------
//  KeyframeModel
// -----------------------------------
class KeyframeModel : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit KeyframeModel(QObject* parent = nullptr);
	virtual ~KeyframeModel(void);
};

