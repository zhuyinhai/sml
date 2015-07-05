#pragma once

#include <QAbstractItemModel>
#include <QStandardItem>

class TextureListItemBase;
class TextureFolder;

// -----------------------------------
//  ItemListModel
// -----------------------------------
class ItemListModel : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit ItemListModel(QObject* parent = nullptr);
	virtual ~ItemListModel(void);

	QVariant data(const QModelIndex &index, int role) const override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	Qt::DropActions supportedDropActions(void) const override;

	bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
		const QModelIndex &destinationParent, int destinationChild) override;
};

Q_DECLARE_METATYPE(ItemListModel*);
