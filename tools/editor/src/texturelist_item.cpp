
#include "texturelist_item.h"


// -----------------------------------
//  TextureListItemBase
// -----------------------------------
TextureListItemBase::TextureListItemBase(void)
	: parent_(Q_NULLPTR)
{}

TextureListItemBase::~TextureListItemBase(void)
{}

void TextureListItemBase::setParent(TextureListItemBase* parent)
{
	parent_ = parent;
}

TextureListItemBase* TextureListItemBase::getParent(void)
{
	return parent_;
}

void TextureListItemBase::setName(const QString& name)
{
	name_ = name;
}

const QString& TextureListItemBase::getName(void) const
{
	return name_;
}



// -----------------------------------
//  TextureItem
// -----------------------------------
TextureItem::TextureItem(void)
	: compressType_(CompressType::MAX)
{}

TextureItem::~TextureItem(void)
{}

int TextureItem::getChildCount(void) const
{
	return 0;
}

TextureListItemBase* TextureItem::getChild(int)
{
	return nullptr;
}

int TextureItem::getColomnCount(void) const
{
	return 3; // name, path, compressType
}

QVariant TextureItem::getColumn(int column)
{
	switch(column)
	{
	case 0: return getName();
	case 1: return path_;
	case 2: return "";
	default:
		break;
	}
	return QVariant();
}


int TextureItem::getRow(TextureListItemBase*) const
{
	return -1; // invalid index
}


// -----------------------------------
//  TextureFolder
// -----------------------------------
TextureFolder::TextureFolder(void)
{}

TextureFolder::~TextureFolder(void)
{
	qDeleteAll(list_);
}

int TextureFolder::getChildCount(void) const
{
	return list_.count();
}

TextureListItemBase* TextureFolder::getChild(int row)
{
	return list_[row];
}

int TextureFolder::getColomnCount(void) const
{
	return 1;
}

QVariant TextureFolder::getColumn(int column)
{
	return (0==column)?(getName()):(QVariant());
}

int TextureFolder::getRow(TextureListItemBase* item) const
{
	return list_.indexOf(item, 0);
}

void TextureFolder::addItem(TextureListItemBase* item)
{
	if(!item)
	{
		return;
	}
	item->setParent(this);
	list_.push_back(item);
}