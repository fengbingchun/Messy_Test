#include <iostream>

#include "State_1.hpp"
#include "Context_1.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/33385599

State_3::State_3()
{

}

State_3::~State_3()
{

}

void State_3::OperationInterface(Context_3* con)
{
	std::cout<<"State:: ..."<<std::endl;
}

bool State_3::ChangeState(Context_3* con, State_3* st)
{
	con->ChangeState(st);
	return true;
}

void State_3::OperationChangeState(Context_3* con)
{

}

ConcreteStateA_3::ConcreteStateA_3()
{

}

ConcreteStateA_3::~ConcreteStateA_3()
{

}

void ConcreteStateA_3::OperationInterface(Context_3* con)
{
	std::cout<<"ConcreteStateA::OperationInterface ..."<<std::endl;
}

void ConcreteStateA_3::OperationChangeState(Context_3* con)
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateB_3());
}

ConcreteStateB_3::ConcreteStateB_3()
{

}

ConcreteStateB_3::~ConcreteStateB_3()
{

}

void ConcreteStateB_3::OperationInterface(Context_3* con)
{
	std::cout<<"ConcreteStateB::OperationInterface ..."<<std::endl;
}

void ConcreteStateB_3::OperationChangeState(Context_3* con)
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateA_3());
}