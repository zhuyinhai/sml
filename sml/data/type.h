
#pragma once

#include <stdint.h>
#include "sml/config.h"

SML_NAMESPACE_BEGIN

namespace data
{
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using f32 = float;

	using Name = char[32];

	union Signature
	{
		u8 str[4];
		u32 asU32;
	};
	static_assert(sizeof(Signature) == 4, "Signature size check");

	enum class ValueType : u32
	{
		AnchorX,
		AnchorY,
		PositionX,
		PositionY,
		ScaleX,
		ScaleY,
		RotateZ,
		ColorR,
		ColorG,
		ColorB,
		ColorA,
	};

	enum class LayerType : u32
	{
		Composition,
		Plane,
		Sprite,
		NineSliceSprite,
		Text,
		Mask,
	};

	enum class DrawingMode : u32
	{
		Normal,
		Add,
		Multiply,
	};

	struct Size
	{
		u16 width;
		u16 height;
	};
	static_assert(sizeof(Size) == 4, "Size size check");

	struct Rect
	{
		f32 left;
		f32 right;
		f32 top;
		f32 bottom;
	};
	static_assert(sizeof(Rect) == 16, "Rect size check");

	struct Color
	{
		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};
	static_assert(sizeof(Color) == 4, "Color size check");

	struct BezierValue
	{
		f32 value;
		f32 in;
		f32 out;
	};
	static_assert(sizeof(BezierValue) == 12, "BezierValue size check");

	struct Keyframe
	{
		f32 frame;
		ValueType type;

		union
		{
			BezierValue bezierValue;
			f32 value;
			u8 colorValue;
		};
	};
	static_assert(sizeof(Keyframe) == 20, "Keyframe size check");

	template<typename KeyframeValue> 
	KeyframeValue getKeyframeValue(const Keyframe& keyframe);

	template<>
	inline BezierValue getKeyframeValue<BezierValue>(const Keyframe& keyframe){ return keyframe.bezierValue; }

	template<>
	inline f32 getKeyframeValue<f32>(const Keyframe& keyframe){ return keyframe.value; }

	template<>
	inline u8 getKeyframeValue<u8>(const Keyframe& keyframe){ return keyframe.colorValue; }
}

SML_NAMESPACE_END


