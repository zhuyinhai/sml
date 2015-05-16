
template<typename Config>
Layer<Config>::Layer(Composition* composition)
	: data_(nullptr)
	, composition_(composition)
	, index_(0)
{}

template<typename Config>
Layer<Config>::~Layer(void)
{}

template<typename Config>
auto Layer<Config>::toComposition(void) ->Composition*
{
	return composition_;
}

template<typename Config>
size_t Layer<Config>::getIndex(void) const
{
	return index_;
}

template<typename Config>
template<typename NameType>
void Layer<Config>::setName(NameType name)
{
	NameTraits<Name>::copy(name_, name);
}

template<typename Config>
auto Layer<Config>::getName(void) const ->const Name&
{
	return name_;
}

template<typename Config>
void Layer<Config>::store(const Matrix& matrix)
{
	MatrixTraits<Matrix>::store(storeMatrix_, matrix);
}

template<typename Config>
void Layer<Config>::store(const Color& color)
{
	ColorTraits<Color>::copy(storeColor_, color);
}

template<typename Config>
void Layer<Config>::load(Matrix& matrix)
{
	MatrixTraits<Matrix>::load(matrix, storeMatrix_);
}

template<typename Config>
void Layer<Config>::load(Color& color)
{
	ColorTraits<Color>::copy(color, storeColor_);
}

template<typename Config>
void Layer<Config>::setData(const data::Layer* data)
{
	data_ = data;
}

template<typename Config>
const data::Layer* Layer<Config>::getData(void) const
{
	return data_;
}