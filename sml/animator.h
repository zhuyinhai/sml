
#pragma once

#include "sml/composition.h"

SML_NAMESPACE_BEGIN

// ----------------------
// Animator
// ----------------------
template<typename Config>
class Animator : public Composition<Config>
{
	SML_NONCOPYABLE(Animator)
	SML_CONFIG_TYPE
public:
	Animator(void);

	template<typename NameType>
	Animator(NameType name);

	virtual ~Animator(void);

	void assignLayerIndex(void);
	void dumpLayers(void);

	template<typename Path, typename NameType>
	bool setState(Path path, NameType state);
};

#include "sml/inl/animator.inl"

SML_NAMESPACE_END