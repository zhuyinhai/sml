
#pragma once

#include "sml/config.h"

SML_NAMESPACE_BEGIN

namespace data
{
	// ----------------------
	// Array
	// ----------------------
	template<typename T>
	class Array
	{
		using const_pointer = const T*;
		using const_reference = const T&;
	public:
		Array(void);
		virtual ~Array(void);

		Array& operator=(const Array& rhs);

		void set(const_pointer ptr, size_t size);
		void clear(void);

		const_reference operator[](size_t index) const;

		const_pointer begin(void) const;
		const_pointer end(void) const;
		size_t size(void) const;

		template<typename Func>
		size_t count(Func func) const;

	private:
		const_pointer ptr_;
		size_t size_;
	};


	// ------------------------- 

	template<typename T>
	Array<T>::Array(void)
		: ptr_(nullptr)
		, size_(0)
	{}

	template<typename T>
	Array<T>::~Array(void)
	{}


	template<typename T>
	auto Array<T>::operator=(const Array& rhs) ->Array&
	{
		ptr_ = rhs.ptr_;
		size_ = rhs.size_;
		return *this;
	}

	template<typename T>
	void Array<T>::set(const_pointer ptr, size_t size)
	{
		ptr_ = ptr;
		size_ = size;
	}

	template<typename T>
	void Array<T>::clear(void)
	{
		ptr_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline auto Array<T>::operator[](size_t index) const->const_reference
	{
		SML_ASSERT(index<size_ && nullptr!=ptr_);
		return *(ptr_+index);
	}

	template<typename T>
	inline auto Array<T>::begin(void) const->const_pointer
	{
		return ptr_;
	}

	template<typename T>
	inline auto Array<T>::end(void) const->const_pointer
	{
		SML_ASSERT(nullptr != ptr_ || (nullptr==ptr_ && 0==size_));
		return ptr_+size_;
	}

	template<typename T>
	inline size_t Array<T>::size(void) const
	{
		return size_;
	}

	template<typename T>
	template<typename Func>
	size_t Array<T>::count(Func func) const
	{
		size_t c = 0;
		for(auto& value : *this )
		{
			if( func(value) )
			{
				++c;
			}
		}
		return c;
	}


}

SML_NAMESPACE_END