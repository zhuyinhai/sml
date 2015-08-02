
#include "item/item_handle.h"
#include "item/item_base.h"

#include <limits>
#include <algorithm>
#include <qdatastream.h>


// -----------------------------------
//  ItemHandle
// -----------------------------------
ItemHandle::ItemHandle(void)
	: index_(0)
	, magic_(0)
{}

ItemHandle::ItemHandle(const ItemHandle& rhs)
	: index_(rhs.index_)
	, magic_(rhs.magic_)
{}

ItemHandle::ItemHandle(uint32_t index, uint32_t magic)
	: index_(index)
	, magic_(magic)
{}


ItemHandle& ItemHandle::operator=(const ItemHandle& rhs)
{
	index_ = rhs.index_;
	magic_ = rhs.magic_;
	return *this;
}

ItemBase* ItemHandle::operator->(void)
{
	return get();
}

bool ItemHandle::isNull(void)
{
	return get() == nullptr;
}


ItemBase* ItemHandle::get(void)
{
	return ItemStore::get(index_, magic_);
}

void ItemHandle::release(void)
{
	ItemStore::release(index_, magic_);
}


//  ======================================================= 

QDataStream &operator << (QDataStream &out, const ItemHandle& rhs)
{
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream& operator>>(QDataStream& in, ItemHandle& rhs)
{
	in.readRawData(reinterpret_cast<char *>(&rhs), sizeof(rhs));
	return in;
}



// -----------------------------------
//  ItemStore
// -----------------------------------
ItemStore::ItemStore(void)
	: magic_(0)
{
	memset( data_, 0, sizeof(data_) );

	// -- 
	qRegisterMetaTypeStreamOperators<ItemHandle>("ItemHandle");
}

ItemStore::~ItemStore(void)
{
	for( auto& data : data_ )
	{
		::SafeDelete(data.item);
	}
}


ItemStore& ItemStore::handle(void)
{
	static ItemStore instance;
	return instance;
}

ItemBase* ItemStore::get(uint32_t index, uint32_t magic)
{
	if(index>=ITEM_MAX)
	{
		return nullptr;
	}
	Data& data = handle().data_[index];
	if( data.magic == magic )
	{
		return data.item;
	}
	return nullptr;
}

void ItemStore::release(uint32_t index, uint32_t magic)
{
	if(index >= ITEM_MAX)
	{
		return ;
	}
	Data& data = handle().data_[index];
	if(data.magic == magic)
	{
		::SafeDelete(data.item);
	}
}
