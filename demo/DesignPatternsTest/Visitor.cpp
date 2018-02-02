#include "Visitor.hpp"
#include "Element.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/37058681

Visitor::Visitor()
{

}

Visitor::~Visitor()
{

}

ConcreteVisitorA::ConcreteVisitorA()
{

}

ConcreteVisitorA::~ConcreteVisitorA()
{

}

void ConcreteVisitorA::VisitConcreteElementA(Element* elm)
{
	std::cout << "I will visit ConcreteElementA ..." << std::endl;
}

void ConcreteVisitorA::VisitConcreteElementB(Element* elm)
{
	std::cout << "I will visit ConcreteElementB ..." << std::endl;
}

ConcreteVisitorB::ConcreteVisitorB()
{

}

ConcreteVisitorB::~ConcreteVisitorB()
{

}

void ConcreteVisitorB::VisitConcreteElementA(Element* elm)
{
	std::cout << "I will visit ConcreteElementA ..." << std::endl;
}

void ConcreteVisitorB::VisitConcreteElementB(Element* elm)
{
	std::cout << "I will visit ConcreteElementB ..." << std::endl;
}

int test_Visitor1()
{
	ObjectStructure* os = new ObjectStructure();
	os->Add(new Man());
	os->Add(new Woman());

	Success* success = new Success();
	os->Display(success);

	Failure* fl = new Failure();
	os->Display(fl);

	/*result
		男人成功时，背后有个伟大的女人
		女人成功时，背后有个没用的男人
		男人失败时，背后有个伟大的女人
		女人失败时，背后有个没用的男人
	*/

	return 0;
}

int test_Visitor2()
{
	Visitor* vis = new ConcreteVisitorA();
	Element* elm = new ConcreteElementA();
	elm->Accept(vis);

	/*result
		I will visit ConcreteElementA ...
		visiting ConcreteElementA ...
	*/

	return 0;
}
