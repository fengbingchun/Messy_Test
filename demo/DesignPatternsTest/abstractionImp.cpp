#include "abstractionImp.hpp"
#include <iostream>

AbstractionImp::AbstractionImp()
{

}

AbstractionImp::~AbstractionImp()
{

}

void AbstractionImp::Operation()
{
	std::cout << "AbstractionImp .... imp ..." << std::endl;
}

ConcreteAbstractionImpA::ConcreteAbstractionImpA()
{

}

ConcreteAbstractionImpA::~ConcreteAbstractionImpA()
{

}

void ConcreteAbstractionImpA::Operation()
{
	std::cout << "ConcreteAbstractionImpA ...." << std::endl;
}

ConcreteAbstractionImpB::ConcreteAbstractionImpB()
{

}

ConcreteAbstractionImpB::~ConcreteAbstractionImpB()
{

}

void ConcreteAbstractionImpB::Operation()
{
	std::cout << "ConcreteAbstractionImpB ...." << std::endl;
}