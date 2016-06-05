#include "Context_1.hpp"
#include "State_1.hpp"

Context_3::Context_3()
{

}

Context_3::Context_3(State_3* state)
{
	this->_state = state;
}

Context_3::~Context_3()
{
	delete _state;
}

void Context_3::OperationInterface()
{
	_state->OperationInterface(this);
}

bool Context_3::ChangeState(State_3* state)
{
	//_state->ChangeState(this, state);
	this->_state = state;

	return true;
}

void Context_3::OperationChangeState()
{
	_state->OperationChangeState(this);
}