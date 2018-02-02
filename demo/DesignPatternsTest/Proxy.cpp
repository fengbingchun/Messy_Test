#include "Proxy.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/30976879

Subject_1::Subject_1()
{

}

Subject_1::~Subject_1()
{

}

ConcreteSubject_1::ConcreteSubject_1()
{

}

ConcreteSubject_1::~ConcreteSubject_1()
{

}

void ConcreteSubject_1::Request()
{
	std::cout << "ConcreteSubject ... request ..." << std::endl;
}

Proxy::Proxy()
{

}

Proxy::Proxy(Subject_1* sub)
{
	_sub = sub;
}

Proxy::~Proxy()
{
	delete _sub;
}

void Proxy::Request()
{
	std::cout << "Proxy request ..." << std::endl;
	_sub->Request();
}

int test_Proxy1()
{
	ProxyClass* test = new ProxyClass();
	test->Request();

	/*result
		真实的请求
	*/

	return 0;
}

int test_Proxy2()
{
	Subject_1* sub = new ConcreteSubject_1();
	Proxy* p = new Proxy(sub);
	p->Request();

	/*result
		Proxy request ...
		ConcreteSubject ... request ...
	*/

	return 0;
}
