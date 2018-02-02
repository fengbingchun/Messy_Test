#include "Facade.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/30972323

Subsystem1::Subsystem1()
{

}

Subsystem1::~Subsystem1()
{

}

void Subsystem1::Operation()
{
	std::cout << "Subsystem1 operation ..." << std::endl;
}

Subsystem2::Subsystem2()
{

}

Subsystem2::~Subsystem2()
{

}

void Subsystem2::Operation()
{
	std::cout << "Subsystem2 operation ..." << std::endl;
}

Facade_1::Facade_1()
{
	this->_subs1 = new Subsystem1();
	this->_subs2 = new Subsystem2();
}

Facade_1::~Facade_1()
{
	delete _subs1;
	delete _subs2;
}

void Facade_1::OperationWrapper()
{
	this->_subs1->Operation();
	this->_subs2->Operation();
}

int test_Facade1()
{
	Facade* test = new Facade();
	test->FacadeMethod();

	/*result
		方法一
		方法二
		方法三
	*/

	return 0;
}

int test_Facade2()
{
	Facade_1* f = new Facade_1();
	f->OperationWrapper();

	/*result
		Subsystem1 operation ...
		Subsystem2 operation ...
	*/

	return 0;
}
