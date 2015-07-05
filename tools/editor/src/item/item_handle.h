#pragma once

#include <cstdint>
#include <QMetaType>

class ItemBase;

// -----------------------------------
//  ItemHandle
// -----------------------------------
class ItemHandle
{
public:
	ItemHandle(void);
	ItemHandle(const ItemHandle& rhs);
	ItemHandle(uint32_t index, uint32_t magic);

	~ItemHandle(void) = default;

	ItemHandle& operator=(const ItemHandle& rhs);
	ItemBase* operator->(void);

	bool isNull(void);
	ItemBase* get(void);
	void release(void);

private:
	uint32_t index_;
	uint32_t magic_;
};

//  ======================================================= 

Q_DECLARE_METATYPE(ItemHandle);
QDataStream &operator<<(QDataStream &out, const ItemHandle& rhs);
QDataStream& operator>>(QDataStream& in, ItemHandle& rhs);

// -----------------------------------
//  ItemStore
// -----------------------------------
class ItemStore
{
public:
	virtual ~ItemStore(void);

	template<typename T, typename... Arg>
	static ItemHandle create(Arg... args);

	static ItemBase* get(uint32_t index, uint32_t magic);
	static void release(uint32_t index, uint32_t magic);

private:
	ItemStore(void);
	ItemStore(const ItemStore& rhs) = delete;
	ItemStore& operator=(const ItemStore& rhs) = delete;

	static ItemStore& handle(void);

private:
	enum { ITEM_MAX = 256 };

	struct Data
	{
		ItemBase* item;
		uint32_t magic;
	};

	Data data_[ITEM_MAX];
	uint32_t magic_;
};

template<typename T, typename... Arg>
static ItemHandle ItemStore::create(Arg... args)
{
	Data (&data)[ITEM_MAX] = handle().data_;
	for( uint32_t i=0; i<ITEM_MAX; ++i )
	{
		if( nullptr == data[i].item )
		{
			data[i].magic = ++(handle().magic_);
			data[i].item = new T(args...);
			return ItemHandle(i, data[i].magic);
		}
	}
	return ItemHandle();
}



