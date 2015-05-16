
#pragma once

#include "test_d3d11/sml_config.h"

//---------------------------------------
// Sprite
//---------------------------------------
class Sprite : public sml::Layer<SmlConfig>
{
	using Size = DirectX::XMFLOAT2;
	using Color = DirectX::XMFLOAT4;
public:
	Sprite(void) = default;
	virtual ~Sprite(void) = default;

	void setSize(const Size& size);
	const Size& getSize(void) const;

	void setColor(const Color& color);
	const Color& getColor(void) const;

private:
	Size size_;
	Color color_;
};

inline void Sprite::setSize(const Size& size)
{
	size_ = size;
}

inline const Sprite::Size& Sprite::getSize(void) const
{
	return size_;
}

inline void Sprite::setColor(const Color& color)
{
	color_ = color;
}

inline const Sprite::Color& Sprite::getColor(void) const
{
	return color_;
}
