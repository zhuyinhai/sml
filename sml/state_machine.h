
#pragma once 

#include "sml/state.h"

SML_NAMESPACE_BEGIN

// ----------------------
// StateMachine
// ----------------------
template<typename Config>
class StateMachine
{
	SML_NONCOPYABLE(StateMachine)
	SML_CONFIG_TYPE
	using State = State<Config>;
public:
	StateMachine(void);
	virtual ~StateMachine(void);

	template<typename NameType>
	bool setState(NameType name);

	void append(State& ref);

	void update(f32 deltaTime);

	State* getCurrentState(void);
	f32 getStateTime(void);

private:
	List<State> stateList_;
	State* current_;
	f32 time_;
};

#include "sml/inl/state_machine.inl"

SML_NAMESPACE_END
