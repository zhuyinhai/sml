
#pragma once

#include <windows.h>
#include <directxmath.h>

#include "sml/type.h"
#include "sml/type_traits.h"
#include "sml/animator.h"
#include "sml/path.h"

#include "test_d3d11/trace.h"

struct LogTag {};

struct SmlConfig
{
	using color_type = DirectX::XMFLOAT4;
	using matrix_type = DirectX::XMMATRIX;
	using name_type = char[32];
	using log_type = LogTag;
};

SML_NAMESPACE_BEGIN

// -- NameTraits -- 

template<>
inline const char* NameTraits<SmlConfig::name_type>::toCStr(const SmlConfig::name_type &name)
{
	return name;
}

template<>
template<typename NameType>
bool NameTraits<SmlConfig::name_type>::isEqual(const SmlConfig::name_type &lhs, const NameType& rhs)
{
	return 0 == strcmp(lhs, rhs);
}

template<>
template<typename NameType>
void NameTraits<SmlConfig::name_type>::copy(SmlConfig::name_type &dest, const NameType& src)
{
#if defined(_MSC_VER)
	strcpy_s(dest, src);
#else
	strcpy(dest, src);
#endif
}

// -- MatrixTraits -- 
template<>
struct MatrixTraits<DirectX::XMMATRIX>
{
	using value_type = FLOAT;
	using store_type = DirectX::XMFLOAT4X4;

	inline static DirectX::XMMATRIX XM_CALLCONV identity(void)
	{
		return DirectX::XMMatrixIdentity();
	}

	inline static DirectX::XMMATRIX XM_CALLCONV multiply(DirectX::FXMMATRIX lhs,DirectX::FXMMATRIX rhs)
	{
		return lhs*rhs;
	}

	inline static DirectX::XMMATRIX calc(
		value_type anchorX, value_type anchorY,
		value_type posX, value_type posY,
		value_type scaleX,value_type scaleY,
		value_type rotateZ
		)
	{
		return DirectX::XMMatrixTranslation( -anchorX, -anchorY, 0.f )
			*DirectX::XMMatrixScaling(scaleX, scaleY, 1.f)
			*DirectX::XMMatrixRotationZ(rotateZ )
			*DirectX::XMMatrixTranslation( posX, posY, 0.f );
	}

	inline static void XM_CALLCONV store(DirectX::XMFLOAT4X4& dest,DirectX::FXMMATRIX matrix)
	{
		DirectX::XMStoreFloat4x4(&dest,matrix);
	}

	inline static void XM_CALLCONV load(DirectX::XMMATRIX& matrix, const DirectX::XMFLOAT4X4& src)
	{
		matrix = DirectX::XMLoadFloat4x4( &src );
	}
};


template<>
struct LogTraits<LogTag>
{
	template<typename... Arg>
	inline static void logError(const char* file, int line, Arg... arg)
	{
		trace_output(file, line, arg...);
	}

	template<typename... Arg>
	static void logWarning(const char* file, int line, Arg... arg)
	{
		trace_output(file, line, arg...);
	}

	template<typename... Arg>
	static void logDebug(const char* file, int line, Arg... arg)
	{
		trace_output(file, line, arg...);
	}

};

SML_NAMESPACE_END