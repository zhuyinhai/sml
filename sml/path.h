
#pragma once

#include "sml/type.h"

SML_NAMESPACE_BEGIN

// ----------------------
// PathTraits
// ----------------------
template<typename Path>
struct PathTraits
{
	using iterator = typename Path::iterator;
	static iterator begin(Path& path){ return std::begin(path); }
	static iterator end(Path& path){ return std::end(path); }

	static bool isEmpty(Path& path){ return 0==path.size(); }

};

SML_NAMESPACE_END
