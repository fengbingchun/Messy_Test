#include "SimplyFactory.hpp"
#include "Factory_1.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/24872725

int test_SimplyFactory1()
{
	//CCalculatorFactory* calFactory = new CCalculatorFactory();
	int type = 0;
	double a = 10, b = 2;

	type = 1;
	//COperation* operation = calFactory->CreateOperation((PRODUCTTYPE)type, a, b);
	COperation* operation = CCalculatorFactory::CreateOperation((PRODUCTTYPE)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 2;
	//operation = calFactory->CreateOperation((PRODUCTTYPE)type, a, b);
	operation = CCalculatorFactory::CreateOperation((PRODUCTTYPE)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 3;
	//operation = calFactory->CreateOperation((PRODUCTTYPE)type, a, b);
	operation = CCalculatorFactory::CreateOperation((PRODUCTTYPE)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 4;
	//operation = calFactory->CreateOperation((PRODUCTTYPE)type, a, b);
	operation = CCalculatorFactory::CreateOperation((PRODUCTTYPE)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	/*if (calFactory) {
	delete calFactory;
	calFactory = NULL;
	}*/

	/*result
		COperation constructor
		CAddOperation constructor
		12
		CAddOperation destructor
		COperation destructor
		COperation constructor
		CSubOperation constructor
		8
		CSubOperation destructor
		COperation destructor
		COperation constructor
		CMulOperation constructor
		20
		CMulOperation destructor
		COperation destructor
		COperation constructor
		CDivOperation constructor
		5
		CDivOperation destructor
		COperation destructor
	*/

	return 0;
}

int test_SimplyFactory2()
{
	CCalculatorFactory_1* calFactory = new CCalculatorFactory_1();
	int type = 0;
	double a = 10, b = 2;

	type = 1;
	COperation_1* operation = calFactory->CreateOperation((PRODUCTTYPE_1)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 2;
	operation = calFactory->CreateOperation((PRODUCTTYPE_1)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 3;
	operation = calFactory->CreateOperation((PRODUCTTYPE_1)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = 4;
	operation = calFactory->CreateOperation((PRODUCTTYPE_1)type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	if (calFactory) {
		delete calFactory;
		calFactory = NULL;
	}

	return 0;
}
