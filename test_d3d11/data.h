
#pragma once

#include "test_d3d11/array.h"
#include "test_d3d11/sml_config.h"
#include "sml/data/accessor.h"

// ----------------------
// Data 
// ----------------------
class Data : public sml::data::Accessor<SmlConfig>
{
public:
	struct Count
	{
		Count();

		size_t texture;
		size_t plane;
		size_t sprite;
		size_t nineSprite;
		size_t composition;
		size_t state;
	};

public:
	Data(void)=default;
	virtual ~Data(void)=default;

	bool load(const char* filepath);
	void unload(void);

	void count(Count& dataCount, sml::data::u32 compId);

private:
	Data(const Data&) = delete;
	Data& operator=(const Data&) = delete;

private:
	Array<char> buffer_;
};
