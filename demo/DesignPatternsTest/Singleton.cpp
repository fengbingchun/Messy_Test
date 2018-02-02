#include <iostream>
#include "Singleton.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/22584107

Singleton* Singleton::single = NULL;//静态变量类外初始化

Singleton_1* Singleton_1::_instance = 0;

Singleton_1::Singleton_1()
{
	std::cout << "Singleton ..." << std::endl;
}

Singleton_1* Singleton_1::Instance()
{
	if (_instance == 0)
		_instance = new Singleton_1();

	return _instance;
}

int test_Singleton1()
{
	Singleton* s1 = Singleton::GetInstance();
	Singleton* s2 = Singleton::GetInstance();

	if (s1 == s2)
		std::cout << "ok" << std::endl;
	else
		std::cout << "no" << std::endl;

	/*result:
		ok
	*/

	return 0;
}

int test_Singleton2()
{
	Singleton_1* sgn = Singleton_1::Instance();

	/*result:
		Singleton ...
	*/

	return 0;
}
