
#include <fstream>

#include "test_d3d11/data.h"
#include "test_d3d11/trace.h"

// ----------------------
// Data::Count 
// ----------------------
Data::Count::Count(void)
	: texture(0)
	, plane(0)
	, sprite(0)
	, nineSprite(0)
	, composition(0)
	, state(0)
{}

// ----------------------
// Data 
// ----------------------
bool Data::load(const char* filepath)
{
	std::ifstream ifs;
	ifs.open(filepath, std::ios::in | std::ios::binary);

	if(!ifs.is_open())
	{
		TRACE("Failed to open %s", filepath);
		return false;
	}

	ifs.seekg(0, std::ios::end);
	auto endPos = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	auto startPos = ifs.tellg();
	auto size = static_cast<size_t>(endPos - startPos);

	buffer_.initialize(size);
	ifs.read( buffer_.begin(), size);
	ifs.close();

	return set(buffer_.begin(), size);;
}

void Data::unload(void)
{
	clear();
	buffer_.clear();
}

void Data::count(Count& dataCount, sml::data::u32 compId)
{
	auto itr = getLayers([compId](const sml::data::Layer& data){ return data.compositionId == compId; });
	while(!itr.isEnd())
	{
		using namespace sml::data;
		switch((*itr).type)
		{
		case LayerType::Composition:
		{
			++dataCount.composition;
			dataCount.state += countStates( [compId](const State& state){ return state.compositionId==compId; } );
			count(dataCount, (*itr).typeId);
			break;
		}
		case LayerType::Plane:
		{
			++dataCount.plane;
			break;
		}
		case LayerType::Sprite:
		{
			++dataCount.sprite;
			break;
		}
		case LayerType::NineSliceSprite:
		{
			++dataCount.nineSprite;
			break;
		}
		case LayerType::Text:
		{
			break;
		}
		case LayerType::Mask:
		{
			break;
		}
		}
		++itr;
	}
}