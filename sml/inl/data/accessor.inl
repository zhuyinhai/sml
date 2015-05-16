
template<typename T> inline bool findAll(const T&){ return true; }

inline bool equal(Signature signature, const char* str)
{
	SML_ASSERT(nullptr != str);
	const Signature* temp = reinterpret_cast<const sml::data::Signature*>(str);
	return signature.asU32 == temp->asU32;
}

template<typename T>
inline const T* read(const u8*& pointer)
{
	const sml::data::u8* current = pointer;
	pointer += sizeof(T);
	return reinterpret_cast<const T*>(current);
}

// ----------------------
// Accessor
// ----------------------
template<typename Config>
Accessor<Config>::Accessor(void)
	: header_(nullptr)
{}

template<typename Config>
Accessor<Config>::~Accessor(void)
{}

template<typename Config>
bool Accessor<Config>::set(const void* filedata, size_t filesize)
{
	if(nullptr == filedata)
	{
		return false;
	}
	const u8* begin = reinterpret_cast<const u8*>(filedata);
	const u8* pointer = begin;

	header_ = read<SmlHeader>(pointer);
	if(!equal(header_->signature, "SMLD"))
	{
		SML_ERROR("SmlHeader signature is invalid");
		return false;
	}
	if(header_->versionMajor != SML_VERSION_MAJOR)
	{
		SML_ERROR("SmlHeader version major is invalid");
		return false;
	}
	if(header_->versionMinor != SML_VERSION_MINOR)
	{
		SML_ERROR("SmlHeader version minor is invalid");
		return false;
	}
	if(header_->headerSize != sizeof(SmlHeader))
	{
		SML_ERROR("SmlHeader size is invalid");
		return false;
	}
	if(header_->fileSize != filesize)
	{
		SML_ERROR("SmlHeader filesize is invalid");
		return false;
	}

	while( (size_t)(pointer-begin) < filesize )
	{
		const DataHeader* dataHeader = read<DataHeader>(pointer);
		if(equal(dataHeader->signature, "DOFS" ))
		{
			if( dataHeader->structSize!=sizeof(DataOffset) )
			{
				SML_ERROR("DataOffset size is invalid");
				return false;
			}
			offsets_.set( reinterpret_cast<const DataOffset*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "TEXD"))
		{
			if( dataHeader->structSize!=sizeof(Texture) )
			{
				SML_ERROR("Texture size is invalid");
				return false;
			}
			textures_.set( reinterpret_cast<const Texture*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "PLND"))
		{
			if( dataHeader->structSize!=sizeof(Plane) )
			{
				SML_ERROR("Plane size is invalid");
				return false;
			}
			planes_.set( reinterpret_cast<const Plane*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "SPRT"))
		{
			if( dataHeader->structSize!=sizeof(Sprite) )
			{
				SML_ERROR("Sprite size is invalid");
				return false;
			}
			sprites_.set( reinterpret_cast<const Sprite*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "9SPR"))
		{
			if( dataHeader->structSize != sizeof(NineSliceSprite) )
			{
				SML_ERROR("NineSliceSprite size is invalid");
				return false;
			}
			nineSprites_.set( reinterpret_cast<const NineSliceSprite*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "COMP"))
		{
			if( dataHeader->structSize != sizeof(Composition) )
			{
				SML_ERROR("Composition size is invalid");
				return false;
			}
			compositions_.set( reinterpret_cast<const Composition*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "LAYR"))
		{
			if( dataHeader->structSize != sizeof(Layer) )
			{
				SML_ERROR("Layer size is invalid");
				return false;
			}
			layers_.set( reinterpret_cast<const Layer*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "STAT"))
		{
			if( dataHeader->structSize != sizeof(State) )
			{
				SML_ERROR("State size is invalid");
				return false;
			}
			states_.set( reinterpret_cast<const State*>(pointer), dataHeader->count );
		}
		else if(equal(dataHeader->signature, "SKEY"))
		{
			if( dataHeader->structSize != sizeof(StateKeyframe) )
			{
				SML_ERROR("StateKeyframe size is invalid");
				return false;
			}
			keyframes_.set( reinterpret_cast<const StateKeyframe*>(pointer), dataHeader->count );
		}
		else
		{
#if SML_LOG_DEBUG
			char signature[5];
			memcpy(signature, dataHeader->signature.str, 4);
			signature[4] = '\0';
			SML_DEBUG("Unknown signature found:%s", signature);
#endif
		}
		pointer += dataHeader->structSize*dataHeader->count;
	}

	return (size_t)(pointer - begin) == filesize;
}


template<typename Config>
void Accessor<Config>::clear(void)
{
	header_ = nullptr;
	offsets_.clear();
	textures_.clear();
	planes_.clear();
	sprites_.clear();
	nineSprites_.clear();
	compositions_.clear();
	layers_.clear();
	states_.clear();
	keyframes_.clear();
}

template<typename Config>
inline auto Accessor<Config>::getOffsets(void) const->Iterator<DataOffset>
{
	return Iterator<DataOffset>(findAll<DataOffset>, offsets_.begin(), offsets_.end());
}

template<typename Config>
inline auto Accessor<Config>::getTextures(void) const->Iterator<Texture>
{
	return Iterator<Texture>(findAll<Texture>, textures_.begin(), textures_.end());
}

template<typename Config>
inline auto Accessor<Config>::getPlanes(void) const->Iterator<Plane>
{
	return Iterator<Plane>(findAll<Plane>, planes_.begin(), planes_.end());
}

template<typename Config>
inline auto Accessor<Config>::getSprites(void) const->Iterator<Sprite>
{
	return Iterator<Sprite>(findAll<Sprite>, sprites_.begin(). sprites_.end());
}

template<typename Config>
inline auto Accessor<Config>::getNineSliceSprites(void) const->Iterator<NineSliceSprite>
{
	return Iterator<NineSliceSprite>(findAll<NineSliceSprite>, nineSprites_.begin(), nineSprites_.end());
}

template<typename Config>
inline auto Accessor<Config>::getCompositions(void) const->Iterator<Composition>
{
	return Iterator<Composition>(findAll<Composition>, compositions_.begin(), compositions_.end());
}

template<typename Config>
inline auto Accessor<Config>::getLayers(void) const->Iterator<Layer>
{
	return Iterator<Layer>(findAll<Layer>, layers_.begin(), layers_.end());
}

template<typename Config>
inline auto Accessor<Config>::getStates(void) const->Iterator<State>
{
	return Iterator<State>(findAll<State>, state_.begin(), states_.end());
}

template<typename Config>
inline auto Accessor<Config>::getKeyframes(void) const->Iterator<StateKeyframe>
{
	return Iterator<StateKeyframe>(findAll<StateKeyframe>, keyframes_.begin(), keyframes_.end());
}

template<typename Config>
inline size_t Accessor<Config>::countOffsets(void) const
{
	return offsets_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countTextures(void) const
{
	return textures_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countPlanes(void) const
{
	return planes_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countSprites(void) const
{
	return sprites_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countNineSliceSprites(void) const
{
	return nineSprites_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countCompositions(void) const
{
	return compositions_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countLayers(void) const
{
	return layers_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countStates(void) const
{
	return states_.size();
}

template<typename Config>
inline size_t Accessor<Config>::countKeyframes(void) const
{
	return keyframes_.size();
}

template<typename Config>
template<typename Func> 
inline auto Accessor<Config>::getOffsets(Func func) const->Iterator<DataOffset, Func>
{
	return Iterator<DataOffset, Func>( func, offsets_.begin(), offsets_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getTextures(Func func) const->Iterator<Texture, Func>
{
	return Iterator<Texture, Func>( func, textures_.begin(), textures_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getPlanes(Func func) const->Iterator<Plane, Func>
{
	return Iterator<Plane, Func>( func, planes_.begin(), planes_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getSprites(Func func) const->Iterator<Sprite, Func>
{
	return Iterator<Sprite, Func>( func, sprites_.begin(), sprites_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getNineSliceSprites(Func func) const->Iterator<NineSliceSprite, Func>
{
	return Iterator<NineSliceSprite, Func>( func, nineSprites_.begin(), nineSprites_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getCompositions(Func func) const->Iterator<Composition, Func>
{
	return Iterator<Composition, Func>( func, compositions_.begin(), compositions_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getLayers(Func func) const->Iterator<Layer, Func>
{
	return Iterator<Layer, Func>( func, layers_.begin(), layers_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getStates(Func func) const->Iterator<State, Func>
{
	return Iterator<State, Func>( func, states_.begin(), states_.end() );
}

template<typename Config>
template<typename Func>
inline auto Accessor<Config>::getKeyframes(Func func) const->Iterator<StateKeyframe, Func>
{
	return Iterator<StateKeyframe, Func>( func, keyframes_.begin(), keyframes_.end() );
}

template<typename Config>
template<typename Func> 
inline size_t Accessor<Config>::countOffsets(Func func) const
{
	return offsets_.count(func);
}

template<typename Config>
template<typename Func> 
inline size_t Accessor<Config>::countTextures(Func func) const
{
	return textures_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countPlanes(Func func) const
{
	return planes_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countSprites(Func func) const
{
	return sprites_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countNineSliceSprites(Func func) const
{
	return nineSprites_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countCompositions(Func func) const
{
	return compositions_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countLayers(Func func) const
{
	return layers_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countStates(Func func) const
{
	return states_.count(func);
}

template<typename Config>
template<typename Func>
inline size_t Accessor<Config>::countKeyframes(Func func) const
{
	return keyframes_.count(func);
}

