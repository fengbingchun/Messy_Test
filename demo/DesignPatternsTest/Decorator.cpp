#include "Decorator.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29237955

Component_2::Component_2()
{

}

Component_2::~Component_2()
{

}

void Component_2::Operation()
{

}

ConcreteComponent_2::ConcreteComponent_2()
{

}

ConcreteComponent_2::~ConcreteComponent_2()
{

}

void ConcreteComponent_2::Operation()
{
	std::cout << "ConcreteComponent_2 operation ..." << std::endl;
}

Decorator::Decorator(Component_2* com)
{
	this->_com = com;
}

Decorator::~Decorator()
{
	delete _com;
}

void Decorator::Operation()
{

}

ConcreteDecorator::ConcreteDecorator(Component_2* com) : Decorator(com)
{

}

ConcreteDecorator::~ConcreteDecorator()
{

}

void ConcreteDecorator::AddedBehavior()
{
	std::cout << "ConcreteDecorator::AddedBehavior ..." << std::endl;
}

void ConcreteDecorator::Operation()
{
	_com->Operation();
	this->AddedBehavior();
}

int test_Decorator1()
{
	Person_1* p = new Person_1("小李");
	BigTrouser* bt = new BigTrouser();
	TShirts* ts = new TShirts();

	bt->Decorate(p);
	ts->Decorate(bt);
	ts->Show();

	/*result:
		T Shirts
		Big Trouser
		装扮的是：小李
	*/

	return 0;
}

int test_Decorator2()
{
	Component_2* com = new ConcreteComponent_2();
	Decorator* dec = new ConcreteDecorator(com);

	dec->Operation();
	delete dec;

	/*result
		ConcreteComponent operation ...
		ConcreteDecorator::AddedBehavior
	*/

	return 0;
}
