
#pragma once

#include "sml/config.h"
#include "sml/type.h"
#include "sml/data/type.h"

SML_NAMESPACE_BEGIN


// 0 <= param <= 1 
template<typename ValueType>
inline ValueType interpolation(f32 t, ValueType value1, ValueType value2)
{
	return (1.0f - t)*value1 + t*value2;
}

inline f32 interpolation(f32 t, const data::BezierValue& value1, const data::BezierValue& value2)
{
	return (1.f-t)*(1.f-t)*(1.f-t)*value1.value
		+ 3.f*(1.f-t)*(1.f-t)*t*value1.out
		+ 3.f*(1.f-t)*t*t*value2.in 
		+ t*t*t*value2.value;
}

inline f32 interpolation(f32 t, f32 value1, const data::BezierValue& value2)
{
	return (1.f - t)*(1.f - t)*(1.f - t)*value1
		+ 3.f*(1.f - t)*(1.f - t)*t*value1
		+ 3.f*(1.f - t)*t*t*value2.in
		+ t*t*t*value2.value;
}

inline f32 interpolation(f32 t, const data::BezierValue& value1, f32 value2)
{
	return (1.f - t)*(1.f - t)*(1.f - t)*value1.value
		+ 3.f*(1.f - t)*(1.f - t)*t*value1.out
		+ 3.f*(1.f - t)*t*t*value2
		+ t*t*t*value2;
}



SML_NAMESPACE_END
