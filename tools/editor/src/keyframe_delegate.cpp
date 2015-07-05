
#include "keyframe_delegate.h"


// -----------------------------------
//  KeyframeDelegate
// -----------------------------------
KeyframeDelegate::KeyframeDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{}

KeyframeDelegate::~KeyframeDelegate(void)
{}

void KeyframeDelegate::paint(QPainter *painter,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::paint(painter, option, index);
}