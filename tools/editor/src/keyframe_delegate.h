
#pragma once

#include <QStyledItemDelegate>

// -----------------------------------
//  KeyframeDelegate
// -----------------------------------
class KeyframeDelegate : public QStyledItemDelegate
{
public:
	explicit KeyframeDelegate(QObject *parent = nullptr);
	virtual ~KeyframeDelegate(void);

	void paint(QPainter *painter,
		const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};



