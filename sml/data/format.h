
#pragma once 

#include "sml/data/type.h"

SML_NAMESPACE_BEGIN

namespace data
{
	/**
	* data format [signature]
	*
	*
	* SmlHeader [SMLD]
	* DataHeader [DOFS]
	* DataOffset...
	* DataHeader [TEXD]
	* Texture...
	* DataHeader [PLND]
	* Plane...
	* DataHeader [SPRT]
	* Sprite...
	* DataHeader [9SPR]
	* NineSliceSprite...
	* DataHeader [COMP]
	* Composition...
	* DataHeader [LAYR]
	* Layer...
	* DataHeader [STAT]
	* State...
	* DataHeader [SKEY]
	* StateKeyframe...
	*
	*
	**/

	struct SmlHeader
	{
		Signature signature;
		u16 versionMajor;
		u16 versionMinor;
		u32 headerSize;
		u32 fileSize;
	};
	static_assert(sizeof(SmlHeader) == 16, "SmlHeader size check");

	struct DataHeader
	{
		Signature signature;
		u32 structSize;
		u32 count;
	};
	static_assert(sizeof(DataHeader) == 12, "DataHeader size check");

	struct DataOffset
	{
		Signature signature;
		u32 offset;
	};
	static_assert(sizeof(DataOffset) == 8, "DataHeader size check");

	struct Texture
	{
		u32 id;
		Name name;
		Size size;
	};
	static_assert(sizeof(Texture) == 40, "Texture size check");

	struct Plane
	{
		u32 id;
		Name name;
		Size size;
		Color color;
	};
	static_assert(sizeof(Plane) == 44, "Plane size check");

	struct Sprite
	{
		u32 id;
		Name name;
		Size size;
		u32 textureId;
		Rect uv;
	};
	static_assert(sizeof(Sprite) == 60, "Sprite size check");

	struct NineSliceSprite
	{
		u32 id;
		Name name;
		Size size;
		u32 textureId;
		Rect uv;
		Rect innerRect;
	};
	static_assert(sizeof(NineSliceSprite) == 76, "NineSliceSprite size check");

	struct Composition
	{
		u32 id;
		Name name;
	};
	static_assert(sizeof(Composition) == 36, "Composition size check");

	struct Layer
	{
		u32 id;
		u32 compositionId;
		LayerType type;
		u32 typeId;
		Name name;

		// default transform

		f32 anchorX;
		f32 anchorY;
		f32 posX;
		f32 posY;
		f32 scaleX;
		f32 scaleY;
		f32 rotateZ;
		Color color;

		DrawingMode drawingMode;
	};
	static_assert(sizeof(Layer) == 84, "Layer size check");

	struct State
	{
		u32 id;
		u32 compositionId;
		Name name;
		f32 duration;
		u32 nextStateId;
	};
	static_assert(sizeof(State) == 48, "State size check");

	struct StateKeyframe
	{
		u32 stateId;
		u32 layerId;
		Keyframe keyframe;
	};
	static_assert(sizeof(StateKeyframe) == 28, "StateKeyframe size check");


}

SML_NAMESPACE_END
