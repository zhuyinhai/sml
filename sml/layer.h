
#pragma once

#include "sml/type.h"
#include "sml/type_traits.h"
#include "sml/list.h"

#include "sml/data/format.h"

SML_NAMESPACE_BEGIN

template<typename Config>
class Composition;

// ----------------------
// Layer
// ----------------------
template<typename Config>
class Layer : public List<Layer<Config>>::Node
{
	SML_NONCOPYABLE(Layer)
	SML_CONFIG_TYPE
	
	using Composition = Composition<Config>;
	friend class Composition;

	using StoredMatrix = typename MatrixTraits<Matrix>::store_type;

protected:
	Layer(Composition* composition = nullptr);
public:
	virtual ~Layer(void);

	Composition* toComposition(void);
	
	size_t getIndex(void) const;

	template<typename NameType>
	void setName(NameType name);

	const Name& getName(void) const;

	void store(const Matrix& matrix);
	void store(const Color& color);

	void load(Matrix& matrix);
	void load(Color& color);

	void setData(const data::Layer* data);
	const data::Layer* getData(void) const;

private:
	const data::Layer* data_;
	Composition* composition_;
	Name name_;
	size_t index_;

	typename MatrixTraits<Matrix>::store_type storeMatrix_;
	Color storeColor_;
};

#include "sml/inl/layer.inl"

SML_NAMESPACE_END