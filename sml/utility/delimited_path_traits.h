
#pragma once

#include "sml/config.h"
#include "sml/type_traits.h"

SML_NAMESPACE_BEGIN

template<typename T, T Delimiter>
struct DelimitedPathTraits
{
	struct value_type
	{
		const T* ptr;
		size_t count;

		friend bool operator==(const value_type& lhs, const value_type& rhs){ return lhs.ptr == rhs.ptr; }
		friend bool operator!=(const value_type& lhs, const value_type& rhs){ return lhs.ptr != rhs.ptr; }

		friend bool operator==(const T* lhs, const value_type& rhs)
		{ 
			return length(lhs) == rhs.count && 0 == memcmp(lhs, rhs.ptr, sizeof(T)*rhs.count);
		}
		friend bool operator!=(const T* lhs, const value_type& rhs){ return !(lhs.ptr==rhs.ptr); }
		friend bool operator==(const value_type& lhs, const T* rhs){ return rhs == lhs; }
		friend bool operator!=(const value_type& lhs, const T* rhs){ return rhs != lhs; }
	};

	class iterator
	{
	public:
		using reference = value_type&;
		using const_reference = const value_type&;
	public:
		iterator(const char* ptr)
		{
			value_.ptr = ptr;
			count();
		}

		reference operator*(void) { return value_; }
		const_reference operator*(void) const { return value_; }

		reference operator++(void)
		{
			do
			{
				++value_.ptr;
			} while(*value_.ptr != Delimiter && *value_.ptr != '\0');

			if(*value_.ptr == Delimiter)
			{
				++value_.ptr;
			}
			count();
			return value_;
		}

		bool operator==(const iterator& rhs) const { return value_ == rhs.value_; }
		bool operator!=(const iterator& rhs) const { return value_ != rhs.value_; }

	private:
		void count(void)
		{
			value_.count = 0;
			const char* counter = value_.ptr;

			while(*counter != Delimiter && *counter != '\0')
			{
				++value_.count;
				++counter;
			}
		}

	private:
		value_type value_;
	};

	static size_t length(const char* str){ return strlen(str); }
	static size_t length(const wchar_t* str){ return wcslen(str); }

	static iterator begin(const T* path){ return iterator(path); }
	static iterator end(const T* path){ return iterator(path + length(path)); };
};

SML_NAMESPACE_END