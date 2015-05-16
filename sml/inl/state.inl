

template<typename Config>
State<Config>::State(void)
	: data_(nullptr)
{}

template<typename Config>
State<Config>::~State(void)
{}

template<typename Config>
void State<Config>::setData(const data::State* data,const data::Array<data::StateKeyframe>& keyframes)
{
	data_ = data;
	keyframes_ = keyframes;
}

template<typename Config>
template<typename NameType>
void State<Config>::setName(NameType name)
{
	NameTraits<Name>::copy(name_, name);
}

template<typename Config>
auto State<Config>::getName(void) const ->const Name&
{
	return name_;
}

template<typename Config>
f32 State<Config>::getDuration(void) const
{
	return (nullptr!=data_)?data_->duration:0.0f;
}

template<typename Config>
data::u32 State<Config>::getId(void) const
{
	return (nullptr!=data_)?data_->id:0;
}

template<typename Config>
data::u32 State<Config>::getNextId(void) const
{
	return (nullptr!=data_)?data_->nextStateId:0;
}

template<typename Config>
auto State<Config>::getMatrix(const data::Layer* layer,f32 time) ->Matrix
{
	if(nullptr==layer)
	{
		return MatrixTraits<Matrix>::identity();
	}

	f32 anchorX = getValue<data::BezierValue>(layer->id, layer->anchorX, time, data::ValueType::AnchorX);
	f32 anchorY = getValue<data::BezierValue>(layer->id, layer->anchorY, time, data::ValueType::AnchorY);
	f32 posX = getValue<data::BezierValue>(layer->id, layer->posX, time, data::ValueType::PositionX);
	f32 posY = getValue<data::BezierValue>(layer->id, layer->posY, time, data::ValueType::PositionY);
	f32 scaleX = getValue<f32>(layer->id, layer->scaleX, time, data::ValueType::ScaleX);
	f32 scaleY = getValue<f32>(layer->id, layer->scaleY, time, data::ValueType::ScaleY);
	f32 rotateZ = getValue<f32>(layer->id, layer->rotateZ, time, data::ValueType::RotateZ);

	return MatrixTraits<Matrix>::calc(
		anchorX, anchorY,
		posX, posY,
		scaleX, scaleY,
		rotateZ );
}

template<typename Config>
template<typename KeyframeValue>
f32 State<Config>::getValue(data::u32 layerId, f32 value, f32 time, data::ValueType vt)
{
	auto find = [this, layerId, vt](const data::StateKeyframe& keyframe){
		return keyframe.layerId==layerId &&
			keyframe.stateId==data_->id &&
			keyframe.keyframe.type == vt;
	};
	auto itr = data::Iterator<data::StateKeyframe, decltype(find)>(find, keyframes_.begin(), keyframes_.end());
	
	const data::StateKeyframe* before = nullptr;
	const data::StateKeyframe* after = nullptr;

	while(!itr.isEnd())
	{
		if(itr->keyframe.frame == time)
		{
			// value and bezierValue.value will be same. 
			return itr->keyframe.value;
		}
		else if(itr->keyframe.frame < time)
		{
			if(nullptr == before || before->keyframe.frame<itr->keyframe.frame)
			{
				before = &(*itr);
			}
		}
		else // if( itr->keyframe.frame > time )
		{
			if(nullptr == after || after->keyframe.frame>itr->keyframe.frame)
			{
				after = &(*itr);
			}
		}
		++itr;
	}
	if(nullptr != before && nullptr != after)
	{
		return interpolation(
			(time - before->keyframe.frame) / (after->keyframe.frame - before->keyframe.frame),
			data::getKeyframeValue<KeyframeValue>(before->keyframe),
			data::getKeyframeValue<KeyframeValue>(after->keyframe));
	}
	else if(nullptr != before)
	{
		return interpolation(
			(time - before->keyframe.frame) / (data_->duration - before->keyframe.frame),
			data::getKeyframeValue<KeyframeValue>(before->keyframe),
			value);
	}
	else if(nullptr != after)
	{
		return interpolation(
			time / after->keyframe.frame,
			value,
			data::getKeyframeValue<KeyframeValue>(after->keyframe));
	}
	return value;
}