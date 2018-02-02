#include "Adapter.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29191955

Target::Target()
{

}

Target::~Target()
{

}

void Target::Request()
{
	std::cout << "Target::Request" << std::endl;
}

Adaptee::Adaptee()
{

}

Adaptee::~Adaptee()
{

}

void Adaptee::SpecificRequest()
{
	std::cout << "Adaptee::SpecificRequest" << std::endl;
}

Adapter::Adapter()
{

}

Adapter::~Adapter()
{

}

void Adapter::Request()
{
	this->SpecificRequest();
}

Target4::Target4()
{

}

Target4::~Target4()
{

}

void Target4::Request()
{
	std::cout << "Target::Request" << std::endl;
}

Adaptee4::Adaptee4()
{

}

Adaptee4::~Adaptee4()
{

}

void Adaptee4::SpecificRequest()
{
	std::cout << "Adaptee::SpecificRequest" << std::endl;
}

Adapter4::Adapter4(Adaptee4* ade)
{
	this->_ade = ade;
}

Adapter4::~Adapter4()
{

}

void Adapter4::Request()
{
	_ade->SpecificRequest();
}

int test_Adapter1()
{
	Adapter_* ada = new Adapter_();
	ada->Request();
	delete ada;

	/*result
		特殊的请求
		普通的请求
	*/

	return 0;
}

int test_Adapter2()
{
	Player* p = new TransLater("小李");
	p->Attack();

	/*result
		小李中场进攻
	*/

	return 0;
}

int test_Adapter3()
{
	//Adapter* adt = new Adapter();
	Target* adt = new Adapter();

	adt->Request();

	/*result
		Adaptee::SpecificRequest
	*/

	return 0;
}

int test_Adapter4()
{
	Adaptee4* ade = new Adaptee4;
	Target4* adt = new Adapter4(ade);

	adt->Request();

	/*result
		Adaptee::SpecificRequest
	*/

	return 0;
}
