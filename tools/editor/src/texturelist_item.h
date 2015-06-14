#pragma once

#include <QString>
#include <QVariant.h>


// -----------------------------------
//  TextureListItemBase
// -----------------------------------
class TextureListItemBase
{
public:
	TextureListItemBase(void);
	virtual ~TextureListItemBase(void);

	void setParent(TextureListItemBase* parent);
	TextureListItemBase* getParent(void);

	void setName(const QString& name);
	const QString& getName(void) const;

	virtual int getChildCount(void) const = 0;
	virtual TextureListItemBase* getChild(int row) = 0;

	virtual int getColomnCount(void) const = 0;
	virtual QVariant getColumn(int column) = 0;

	virtual int getRow(TextureListItemBase* item) const = 0;
private:
	TextureListItemBase* parent_;
	QString name_;
};



// -----------------------------------
//  TextureItem
// -----------------------------------
class TextureItem : public TextureListItemBase
{
public:
	enum class CompressType
	{
		UNCOMPRESSED,

		MAX
	};
public:
	TextureItem(void);
	virtual ~TextureItem(void);

	int getChildCount(void) const Q_DECL_OVERRIDE;
	TextureListItemBase* getChild(int row) Q_DECL_OVERRIDE;

	int getColomnCount(void) const Q_DECL_OVERRIDE;
	QVariant getColumn(int column) Q_DECL_OVERRIDE;

	int getRow(TextureListItemBase* item) const Q_DECL_OVERRIDE;

private:
	QString path_;
	CompressType compressType_;
};

// -----------------------------------
//  TextureFolder
// -----------------------------------
class TextureFolder : public TextureListItemBase
{
public:
	TextureFolder(void);
	virtual ~TextureFolder(void);

	int getChildCount(void) const Q_DECL_OVERRIDE;
	TextureListItemBase* getChild(int row) Q_DECL_OVERRIDE;

	int getColomnCount(void) const Q_DECL_OVERRIDE;
	QVariant getColumn(int column) Q_DECL_OVERRIDE;

	int getRow(TextureListItemBase* item) const Q_DECL_OVERRIDE;
	void addItem(TextureListItemBase* item);

private:
	QList<TextureListItemBase*> list_;
};

