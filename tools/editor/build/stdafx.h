
#pragma once

template<typename T>
inline void SafeDelete(T*& ptr)
{
	if(ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

