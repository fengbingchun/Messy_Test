#include "TemplateMethod.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/30990475

AbstractClass_1::AbstractClass_1()
{

}

AbstractClass_1::~AbstractClass_1()
{

}

void AbstractClass_1::TemplateMethod()
{
	this->PrimitiveOperation1();
	this->PrimitiveOperation2();
}

ConcreteClass1_1::ConcreteClass1_1()
{

}

ConcreteClass1_1::~ConcreteClass1_1()
{

}

void ConcreteClass1_1::PrimitiveOperation1()
{
	std::cout << "ConcreteClass1 ... PrimitiveOperation1" << std::endl;
}

void ConcreteClass1_1::PrimitiveOperation2()
{
	std::cout << "ConcreteClass1 ... PrimitiveOperation2" << std::endl;
}

ConcreteClass2_1::ConcreteClass2_1()
{

}

ConcreteClass2_1::~ConcreteClass2_1()
{

}

void ConcreteClass2_1::PrimitiveOperation1()
{
	std::cout << "ConcreteClass2 ... PrimitiveOperation1" << std::endl;
}

void ConcreteClass2_1::PrimitiveOperation2()
{
	std::cout << "ConcreteClass2 ... PrimitiveOperation2" << std::endl;
}

int test_TemplateMethod1()
{
	Naruto* man = new Naruto();
	man->Show();

	OnePice* man2 = new OnePice();
	man2->Show();

	/*result
		我是火影史上最帅的六代目----一鸣惊人naruto
		我是我是无恶不作的大海贼----路飞
	*/

	return 0;
}

int test_TemplateMethod2()
{
	AbstractClass_1* p1 = new ConcreteClass1_1();
	AbstractClass_1* p2 = new ConcreteClass2_1();
	p1->TemplateMethod();
	p2->TemplateMethod();

	/*result
		ConcreteClass1 ... PrimitiveOperation1
		ConcreteClass1 ... PrimitiveOperation2
		ConcreteClass2 ... PrimitiveOperation1
		ConcreteClass2 ... PrimitiveOperation2
	*/

	return 0;
}
