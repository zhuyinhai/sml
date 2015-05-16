
#pragma once

#include "sml/layer.h"
#include "sml/state_machine.h"
#include "sml/path.h"

SML_NAMESPACE_BEGIN

// ----------------------
// Composition
// ----------------------
template<typename Config>
class Composition : public Layer<Config>
{
	SML_NONCOPYABLE(Composition)
	SML_CONFIG_TYPE
public:
	using Layer = Layer<Config>;
public:
	Composition(void);
	virtual ~Composition(void);
	
	void append(Layer& layer);
	void append(State<Config>& state);

	template<typename NameType>
	bool setState(NameType name);

	void update(const Matrix& parentMatrix, f32 deltaTime);

protected:
	template<typename Path>
	Layer* getLayer(Path path);

	void assignLayerIndex(size_t& index);
	void dumpLayers(size_t depth);

	// bool setState(const char* stateName);

private:
	List<Layer> layerList_;
	StateMachine<Config> stateMachine_;
	List<State<Config>> stateList_;
	State<Config>* state_;
};

#include "sml/inl/composition.inl"

SML_NAMESPACE_END