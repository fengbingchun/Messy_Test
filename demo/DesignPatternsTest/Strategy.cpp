#include <iostream>
#include "Strategy.hpp"
#include "Context_2.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/32179281

Strategy_4::Strategy_4()
{

}

Strategy_4::~Strategy_4()
{
	std::cout << "~Strategy ..." << std::endl;
}

void Strategy_4::AlgrithmInterface()
{

}

ConcreteStrategyA_4::ConcreteStrategyA_4()
{

}

ConcreteStrategyA_4::~ConcreteStrategyA_4()
{
	std::cout << "~ConcreteStrategy ..." << std::endl;
}

void ConcreteStrategyA_4::AlgrithmInterface()
{
	std::cout << "test ConcreteStrategyA ..." << std::endl;
}

ConcreteStrategyB_4::ConcreteStrategyB_4()
{

}

ConcreteStrategyB_4::~ConcreteStrategyB_4()
{
	std::cout << "~ConcreteStrategyB ..." << std::endl;
}

void ConcreteStrategyB_4::AlgrithmInterface()
{
	std::cout << "test ConcreteStrategyB ..." << std::endl;
}

int test_Strategy1()
{
	int a, b;
	char c;
	std::cin >> a >> b;
	std::cout << "ÇëÊäÈëÔËËã·û£º";
	std::cin >> c;

	switch (c)
	{
	case '+':
	{
		Context_2* context = new Context_2(new AddOperation(a, b));
		std::cout << context->GetResult() << std::endl;
		break;
	}
	default:
		break;
	}

	/*result
		5
		8
		ÇëÊäÈëÔËËã·û£º+
		13
	*/

	return 0;
}

int test_Strategy2()
{
	int a, b;
	std::cin >> a >> b;
	Context_3* test = new Context_3('+');
	std::cout << test->GetResult() << std::endl;

	/*result
		2
		5
		13
	*/

	return 0;
}

int test_Strategy3()
{
	Strategy_4* ps = new ConcreteStrategyA_4();
	Context_4* pc = new Context_4(ps);
	pc->DoAction();

	if (NULL != pc)
		delete pc;

	/*result
		test ConcreteStrategyA ...
	*/

	return 0;
}
