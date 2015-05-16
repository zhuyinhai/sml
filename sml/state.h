
#pragma once

#include "sml/type.h"
#include "sml/list.h"
#include "sml/data/format.h"
#include "sml/data/array.h"
#include "sml/data/iterator.h"
#include "sml/interpolation.h"

SML_NAMESPACE_BEGIN

template<typename Config>
class Layer;

// ----------------------
// State
// ----------------------
template<typename Config>
class State : public List<State<Config>>::Node
{
	SML_NONCOPYABLE(State)
protected:
	SML_CONFIG_TYPE
	using Layer = Layer<Config>;
public:
	State(void);
	virtual ~State(void);

	void setData(const data::State* data, const data::Array<data::StateKeyframe>& keyframes);

	template<typename NameType>
	void setName(NameType name);

	const Name& getName(void) const;

	f32 getDuration(void) const;
	data::u32 getId(void) const;
	data::u32 getNextId(void) const;

	virtual Matrix getMatrix(const data::Layer* layer, f32 time);

private:
	template<typename KeyframeValue>
	f32 getValue(data::u32 layerId, f32 defaultValue, f32 time, data::ValueType vt);

private:
	Name name_;
	const data::State* data_;
	data::Array<data::StateKeyframe> keyframes_;
};

#include "sml/inl/state.inl"

SML_NAMESPACE_END