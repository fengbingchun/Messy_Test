#include <iostream>
#include "Mediator.hpp"
#include "Colleague.hpp"

Colleague_1::Colleague_1()
{
	//_sdt = "";
}

Colleague_1::Colleague_1(Mediator_1* mdt)
{
	this->_mdt = mdt;
	//_sdt = "";
}

Colleague_1::~Colleague_1()
{

}

ConcreteColleagueA_1::ConcreteColleagueA_1()
{

}

ConcreteColleagueA_1::~ConcreteColleagueA_1()
{

}

ConcreteColleagueA_1::ConcreteColleagueA_1(Mediator_1* mdt) : Colleague_1(mdt)
{

}

std::string ConcreteColleagueA_1::GetState()
{
	return _sdt;
}

void ConcreteColleagueA_1::SetState(const std::string& sdt)
{
	_sdt = sdt;
}

void ConcreteColleagueA_1::Action()
{
	_mdt->DoActionFromAtoB();

	std::cout << "State of ConcreteColleagueA:" << this->GetState() << std::endl;
}

ConcreteColleagueB_1::ConcreteColleagueB_1()
{

}

ConcreteColleagueB_1::~ConcreteColleagueB_1()
{

}

ConcreteColleagueB_1::ConcreteColleagueB_1(Mediator_1* mdt) : Colleague_1(mdt)
{

}

void ConcreteColleagueB_1::Action()
{
	_mdt->DoActionFromBtoA();
	
	std::cout << "State of ConcreteColleagueB:" << this->GetState() << std::endl;
}

std::string ConcreteColleagueB_1::GetState()
{
	return _sdt;
}

void ConcreteColleagueB_1::SetState(const std::string& sdt)
{
	_sdt = sdt;
}