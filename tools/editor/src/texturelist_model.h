#pragma once

#include <QAbstractItemModel>

class TextureListItemBase;
class TextureFolder;
// -----------------------------------
//  TextureListModel
// -----------------------------------
class TextureListModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TextureListModel(QObject* parent);
	virtual ~TextureListModel(void);

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

	TextureFolder* newFolder(const QString& name);
private:
	TextureFolder* root_;
};

