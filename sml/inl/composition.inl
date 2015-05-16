

template<typename Config>
Composition<Config>::Composition(void)
	: Layer(this)
{}

template<typename Config>
Composition<Config>::~Composition(void)
{}

template<typename Config>
void Composition<Config>::append(Layer& layer)
{
	layerList_.pushBack(layer);
}

template<typename Config>
void Composition<Config>::append(State<Config>& state)
{
	stateMachine_.append(state);
}

template<typename Config>
template<typename NameType>
bool Composition<Config>::setState(NameType name)
{
	return stateMachine_.setState(name);
}

template<typename Config>
void Composition<Config>::update(const Matrix& parentMatrix,f32 deltaTime)
{
	stateMachine_.update(deltaTime);

	if(auto state = stateMachine_.getCurrentState())
	{
		for(auto& child : layerList_)
		{
			Matrix matrix = MatrixTraits<Matrix>::multiply(
				state->getMatrix(child.getData(), stateMachine_.getStateTime() ),
				parentMatrix );

			child.store(matrix);
			if(Composition* composition = child.toComposition())
			{
				composition->update(matrix, deltaTime);
			}
		}
	}
	else
	{
		for(auto& child : layerList_)
		{
			if( auto data = child.getData() )
			{
				Matrix matrix = MatrixTraits<Matrix>::multiply(
					MatrixTraits<Matrix>::calc(
					data->anchorX, data->anchorY,
					data->posX, data->posY,
					data->scaleX, data->scaleY,
					data->rotateZ ),
					parentMatrix );

				child.store(matrix);
				if(Composition* composition = child.toComposition())
				{
					composition->update(matrix, deltaTime);
				}
			}
			else
			{
				child.store(parentMatrix);
				if(Composition* composition = child.toComposition())
				{
					composition->update(parentMatrix, deltaTime);
				}
			}
			
		}
	}

}

template<typename Config>
template<typename Path>
auto Composition<Config>::getLayer(Path path)->Layer*
{
	if(PathTraits<Path>::isEmpty(path))
	{
		return this;
	}

	auto itr = PathTraits<Path>::begin(path);
	auto end = PathTraits<Path>::end(path);

	Layer* layer = this;
	while(itr!=end)
	{
		Composition* composition = layer->toComposition();
		if(nullptr==composition)
		{
			return nullptr;
		}
		layer = nullptr;

		for(auto& child : composition->layerList_)
		{
			if(NameTraits<Name>::isEqual(child.getName(),*itr))
			{
				layer = &child;
			}
		}
		if(nullptr==layer)
		{
			return nullptr;
		}
		++itr;
	}
	return layer;
}

template<typename Config>
void Composition<Config>::assignLayerIndex(size_t& index)
{
	index_ = index++;
	for(auto& child : layerList_)
	{
		Composition* composition = child.toComposition();
		if(nullptr!=composition)
		{
			composition->assignLayerIndex(index);
		}
		else
		{
			child.index_ = index++;
		}
	}
}

template<typename Config>
void Composition<Config>::dumpLayers(size_t depth)
{
	static const char* depthFormat[] ={
		"%s [%d]",
		"  + %s [%d]",
		"    + %s [%d]",
		"      + %s [%d]",
		"        + %s [%d]",
		"          + %s [%d]",
	};

	for(auto& child : layerList_)
	{
		if(depth < sizeof(depthFormat)/sizeof(depthFormat[0]))
		{
			SML_DEBUG(depthFormat[depth],NameTraits<Name>::toCStr(child.getName()), child.index_);
		}
		else
		{
			SML_DEBUG("          ...+ %s [%d]",NameTraits<Name>::toCStr(child.getName()), child.index_);
		}
		Composition* composition = child.toComposition();
		if(nullptr!=composition)
		{
			composition->dumpLayers(depth+1);
		}
	}
}