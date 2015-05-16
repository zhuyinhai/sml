
#pragma once

#include "sml/config.h"

SML_NAMESPACE_BEGIN

namespace data
{
	// ----------------------
	// Iterator
	// ----------------------
	template<typename T, typename Func = bool(*)(const T&)>
	class Iterator
	{
		using const_pointer = const T*;
		using const_reference = const T&;
	public:
		Iterator(Func func, const_pointer begin, const_pointer end);
		virtual ~Iterator(void);

		const_reference operator*(void) const;
		const_pointer operator->(void) const;
		Iterator& operator++(void);

		bool isEnd(void) const;

	private:
		Func func_;
		const_pointer ptr_;
		const_pointer end_;
	};

	// ------------------------- 

	template<typename T, typename Func>
	Iterator<T, Func>::Iterator(Func func, const_pointer begin, const_pointer end)
		: func_(func)
		, ptr_(begin)
		, end_(end)
	{
		if( !func_(*ptr_) )
		{
			operator++();
		}
	}

	template<typename T, typename Func>
	Iterator<T, Func>::~Iterator(void)
	{}

	template<typename T, typename Func>
	inline auto Iterator<T, Func>::operator*(void) const ->const_reference
	{
		SML_ASSERT(nullptr != ptr_);
		return *ptr_;
	}

	template<typename T, typename Func>
	inline auto Iterator<T, Func>::operator->(void) const ->const_pointer
	{
		SML_ASSERT(nullptr != ptr_);
		return ptr_;
	}

	template<typename T, typename Func>
	auto Iterator<T, Func>::operator++(void) ->Iterator&
	{
		SML_ASSERT(nullptr!=ptr_&&!isEnd());
		
		do
		{
			++ptr_;
			if( func_(*ptr_) )
			{
				break;
			}
		}while(!isEnd());

		return *this;
	}

	template<typename T, typename Func>
	inline bool Iterator<T, Func>::isEnd(void) const
	{
		return ptr_==end_;
	}
}

SML_NAMESPACE_END