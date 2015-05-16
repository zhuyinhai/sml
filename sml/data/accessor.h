
#pragma once


#include "sml/type.h"
#include "sml/type_traits.h"

#include "sml/data/format.h"
#include "sml/data/array.h"
#include "sml/data/iterator.h"

SML_NAMESPACE_BEGIN

namespace data
{
	// ----------------------
	// Accessor
	// ----------------------
	template<typename Config>
	class Accessor
	{	
		SML_NONCOPYABLE(Accessor)
		SML_CONFIG_TYPE
	public:
		Accessor(void);
		virtual ~Accessor(void);

		Iterator<DataOffset> getOffsets(void) const;
		Iterator<Texture> getTextures(void) const;
		Iterator<Plane> getPlanes(void) const;
		Iterator<Sprite> getSprites(void) const;
		Iterator<NineSliceSprite> getNineSliceSprites(void) const;
		Iterator<Composition> getCompositions(void) const;
		Iterator<Layer> getLayers(void) const;
		Iterator<State> getStates(void) const;
		Iterator<StateKeyframe> getKeyframes(void) const;

		size_t countOffsets(void) const;
		size_t countTextures(void) const;
		size_t countPlanes(void) const;
		size_t countSprites(void) const;
		size_t countNineSliceSprites(void) const;
		size_t countCompositions(void) const;
		size_t countLayers(void) const;
		size_t countStates(void) const;
		size_t countKeyframes(void) const;

		template<typename Func> Iterator<DataOffset, Func> getOffsets(Func func) const;
		template<typename Func> Iterator<Texture, Func> getTextures(Func func) const;
		template<typename Func> Iterator<Plane, Func> getPlanes(Func func) const;
		template<typename Func> Iterator<Sprite, Func> getSprites(Func func) const;
		template<typename Func> Iterator<NineSliceSprite, Func> getNineSliceSprites(Func func) const;
		template<typename Func> Iterator<Composition, Func> getCompositions(Func func) const;
		template<typename Func> Iterator<Layer, Func> getLayers(Func func) const;
		template<typename Func> Iterator<State, Func> getStates(Func func) const;
		template<typename Func> Iterator<StateKeyframe, Func> getKeyframes(Func func) const;

		template<typename Func> size_t countOffsets(Func func) const;
		template<typename Func> size_t countTextures(Func func) const;
		template<typename Func> size_t countPlanes(Func func) const;
		template<typename Func> size_t countSprites(Func func) const;
		template<typename Func> size_t countNineSliceSprites(Func func) const;
		template<typename Func> size_t countCompositions(Func func) const;
		template<typename Func> size_t countLayers(Func func) const;
		template<typename Func> size_t countStates(Func func) const;
		template<typename Func> size_t countKeyframes(Func func) const;

	protected:
		bool set(const void* filedata, size_t filesize);
		void clear(void);

	private:
		const SmlHeader* header_;
		Array<DataOffset> offsets_;
		Array<Texture> textures_;
		Array<Plane> planes_;
		Array<Sprite> sprites_;
		Array<NineSliceSprite> nineSprites_;
		Array<Composition> compositions_;
		Array<Layer> layers_;
		Array<State> states_;
		Array<StateKeyframe> keyframes_;
	};


#include "sml/inl/data/accessor.inl"

}


SML_NAMESPACE_END