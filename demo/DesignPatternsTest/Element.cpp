#include <iostream>
#include "Element.hpp"
#include "Visitor.hpp"

Element::Element()
{

}

Element::~Element()
{

}

void Element::Accept(Visitor* vis)
{

}

ConcreteElementA::ConcreteElementA()
{

}

ConcreteElementA::~ConcreteElementA()
{

}

void ConcreteElementA::Accept(Visitor* vis)
{
	vis->VisitConcreteElementA(this);
	std::cout << "visiting ConcreteElementA ..." << std::endl;
}

ConcreteElementB::ConcreteElementB()
{

}

ConcreteElementB::~ConcreteElementB()
{

}

void ConcreteElementB::Accept(Visitor* vis)
{
	std::cout << "visiting ConcreteElementB ..." << std::endl;
	vis->VisitConcreteElementB(this);
}