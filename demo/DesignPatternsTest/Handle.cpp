#include "Handle.hpp"
#include <iostream>

Handle::Handle()
{
	_succ = 0;
}

Handle::~Handle()
{
	delete _succ;
}

Handle::Handle(Handle* succ)
{
	this->_succ = succ;
}

void Handle::SetSuccessor(Handle* succ)
{
	_succ =  succ;
}

Handle* Handle::GetSuccessor()
{
	return _succ;
}

void Handle::HandleRequest()
{

}

ConcreteHandleA::ConcreteHandleA()
{

}

ConcreteHandleA::ConcreteHandleA(Handle* succ) : Handle(succ)
{

}

ConcreteHandleA::~ConcreteHandleA()
{

}

void ConcreteHandleA::HandleRequest()
{
	if (this->GetSuccessor() != 0) {
		std::cout << "ConcreteHandleA 我把处理权给后继节点 ..." << std::endl;
		this->GetSuccessor()->HandleRequest();
	} else
		std::cout << "ConcreteHandleA 没有后继了， 我必须自己处理 ..." << std::endl;
}

ConcreteHandleB::ConcreteHandleB()
{

}

ConcreteHandleB::ConcreteHandleB(Handle* succ) : Handle(succ)
{

}

ConcreteHandleB::~ConcreteHandleB()
{

}

void ConcreteHandleB::HandleRequest()
{
	if (this->GetSuccessor() != 0) {
		std::cout << "ConcreteHandleB 我把处理权给后继节点 ..." << std::endl;
		this->GetSuccessor()->HandleRequest();
	} else
		std::cout << "ConcreteHandleB 没有后继了，我必须自己处理 ..." << std::endl;
}