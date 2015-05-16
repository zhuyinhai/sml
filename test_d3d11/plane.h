
#pragma once

#include "test_d3d11/sml_config.h"

//---------------------------------------
// Plane
//---------------------------------------
class Plane : public sml::Layer<SmlConfig>
{
public:
	using Size = DirectX::XMFLOAT2;
	using Color = DirectX::XMFLOAT4;
public:
	Plane(void) = default;
	virtual ~Plane(void) = default;

	void setSize(const Size& size);
	const Size& getSize(void) const;

	void setColor(const Color& color);
	const Color& getColor(void) const;

private:
	Size size_;
	Color color_;
};

inline void Plane::setSize(const Size& size)
{
	size_ = size;
}

inline const Plane::Size& Plane::getSize(void) const
{
	return size_;
}

inline void Plane::setColor(const Color& color)
{
	color_ = color;
}

inline const Plane::Color& Plane::getColor(void) const
{
	return color_;}


