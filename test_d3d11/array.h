
#pragma once 

// ----------------------
// Array 
// ----------------------
template<typename T>
class Array
{
public:
	Array(void)
		: pointer_(nullptr)
		, count_(0)
		, capacity_(0)
	{}
	
	virtual ~Array(void)
	{
		clear();
	}

	void initialize(size_t size)
	{
		clear();

		if( 0==size )
		{
			return;
		}

		pointer_ = new T[size];
		capacity_ = size;
		count_ = size;
	}

	void clear(void)
	{
		if( nullptr!=pointer_ )
		{
			delete[] pointer_;
		}
		pointer_ = nullptr;
		count_ = 0;
		capacity_ = 0;
	}

	inline T& operator[](size_t index){ return *(pointer_ + index); };
	
	inline T* begin(void) { return pointer_; }
	inline T* end(void) { return pointer_ + count_; }

	size_t resize(size_t count)
	{
		if( count<=capacity_ )
		{
			count_ = count;
		}
		return count_;
	}
	inline size_t size(void) const { return count_; }

	inline T& next(void)
	{
		assert(count_<capacity_);
		return *(pointer_ + (count_++));
	}

private:
	T* pointer_;
	size_t count_;
	size_t capacity_;
};
