

#if !defined(NDEBUG) && defined(_MSC_VER)
#define NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#else
#define NEW new
#endif

template<typename T>
void SafeDelete(T*& ptr)
{
	if(ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

