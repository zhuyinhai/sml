#pragma once

#include <QAbstractItemModel>
#include <QStandardItem>

class TextureListItemBase;
class TextureFolder;

// -----------------------------------
//  TextureListModel
// -----------------------------------
class TextureListModel : public QStandardItemModel
{
	Q_OBJECT
public:
	TextureListModel(QObject* parent);
	virtual ~TextureListModel(void);

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

	Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
	Qt::DropActions supportedDropActions(void) const Q_DECL_OVERRIDE;

	bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
		const QModelIndex &destinationParent, int destinationChild) Q_DECL_OVERRIDE;
};

Q_DECLARE_METATYPE(TextureListModel*);
