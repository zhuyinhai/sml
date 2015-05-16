
template<typename Config>
StateMachine<Config>::StateMachine(void)
	: current_(nullptr)
	, time_(0.f)
{}

template<typename Config>
StateMachine<Config>::~StateMachine(void)
{}

template<typename Config>
template<typename NameType>
bool StateMachine<Config>::setState(NameType name)
{
	for(auto& state : stateList_)
	{
		if(NameTraits<Name>::isEqual(state.getName(),name))
		{
			current_ = &state;
			time_ = 0.0f;
			return true;
		}
	}
	return false;
}

template<typename Config>
void StateMachine<Config>::append(State& ref)
{
	stateList_.pushBack(ref);
}

template<typename Config>
void StateMachine<Config>::update(f32 deltaTime)
{
	if(nullptr==current_)
	{
		return;
	}
	time_ += deltaTime;
	while(time_ > current_->getDuration())
	{
		time_ -= current_->getDuration();
		for(auto& state : stateList_)
		{
			if(current_->getNextId() == state.getId())
			{
				current_ = &state;
				break;
			}
		}
	}
}

template<typename Config>
auto StateMachine<Config>::getCurrentState(void) ->State*
{
	return current_;
}

template<typename Config>
f32 StateMachine<Config>::getStateTime(void)
{
	return time_;
}