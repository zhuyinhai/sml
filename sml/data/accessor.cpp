
#include "sml/data/accessor.h"
#include "sml/type_traits.h"

SML_NAMESPACE_BEGIN

namespace data
{
	template<typename T> inline bool findAll(const T&){ return true; }

	inline bool equal(Signature signature, const char* str)
	{
		SML_ASSERT(nullptr!=str);
		const Signature* temp = reinterpret_cast<const Signature*>(str);
		return signature.asU32 == temp->asU32;
	}

	// ----------------------
	// Accessor
	// ----------------------
	Accessor::Accessor(void)
		: header_(nullptr)
	{}

	Accessor::~Accessor(void)
	{}

	bool Accessor::set(const void* filedata, size_t filesize)
	{
		if( nullptr==filedata )
		{
			return false;
		}

		const u8* pointer = reinterpret_cast<const u8*>(filedata);
		header_ = reinterpret_cast<const SmlHeader*>(pointer);
		if( !equal(header_->signature, "SMLD") )
		{
			SML_ERROR("");
		}


		return true;
	}


}

SML_NAMESPACE_END