
#pragma once

#include "sml/config.h"

SML_NAMESPACE_BEGIN

template<typename Color>
struct ColorTraits
{
	using value_type = decltype(Color::r);
	
	static value_type r(const Color& color){ return color.r; }
	static value_type g(const Color& color){ return color.g; }
	static value_type b(const Color& color){ return color.b; }
	static value_type a(const Color& color){ return color.a; }

	static void copy(Color& dest, const Color& src){ dest = src; };
	static Color muliply(const Color& lhs, const Color& rhs){ return{ lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b, lhs.a*rhs.a, }; }
};

template<typename Name>
struct NameTraits
{
	static const char* toCStr(const Name& name);

	template<typename Rhs>
	static bool isEqual(const Name& lhs, const Rhs& rhs);

	template<typename NameType>
	static void copy(Name& dest, const NameType& src);
};

template<typename Matrix>
struct MatrixTraits
{
	using value_type = f32;
	using store_type = value_type[16];

	static Matrix identity(void);

	static Matrix multiply(const Matrix& lhs, const Matrix& rhs);

	template<typename Point>
	static Matrix calc(
		value_type anchorX, value_type anchorY,
		value_type posX, value_type posY,
		value_type scaleX, value_type scaleY,
		value_type rotateZ
		);

	static void store(store_type& dest, const Matrix& matrix);
	static void load(Matrix& matrix, const store_type& src);
};

template<typename Log>
struct LogTraits
{
	using filename_type = typename Log::filename_type;
	using line_type = typename Log::line_type;

	template<typename... Arg>
	static void logError(filename_type file, line_type line, Arg... arg);

	template<typename... Arg>
	static void logWarning(filename_type file, line_type line, Arg... arg);

	template<typename... Arg>
	static void logDebug(filename_type file, line_type line, Arg... arg);
};



SML_NAMESPACE_END