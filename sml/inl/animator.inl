

template<typename Config>
Animator<Config>::Animator(void)
{}

template<typename Config>
template<typename NameType>
Animator<Config>::Animator(NameType name)
	: Composition<Config>(name)
{}

template<typename Config>
Animator<Config>::~Animator(void)
{}

template<typename Config>
void Animator<Config>::assignLayerIndex(void)
{
	size_t index = 0;
	Composition<Config>::assignLayerIndex( index );
}


template<typename Config>
void Animator<Config>::dumpLayers(void)
{
	SML_DEBUG("Animator::dumpLayers");
	SML_DEBUG(NameTraits<Name>::toCStr(getName()));
	Composition<Config>::dumpLayers(1);
}

template<typename Config>
template<typename Path, typename StateType>
bool Animator<Config>::setState(Path path, StateType state)
{
	Layer* layer = getLayer(path);
	if(nullptr == layer)
	{
		return false;
	}
	
	Composition<Config>* composition = layer->toComposition();
	if( nullptr==composition )
	{
		return false;
	}

	return composition->setState(state);
}
