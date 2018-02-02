#include "Prototype.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/24130315

Prototype_1::Prototype_1()
{

}

Prototype_1::~Prototype_1()
{

}

Prototype_1* Prototype_1::Clone() const
{
	return 0;
}

ConcretePrototype_1::ConcretePrototype_1()
{

}

ConcretePrototype_1::~ConcretePrototype_1()
{

}

ConcretePrototype_1::ConcretePrototype_1(const ConcretePrototype_1& cp)
{
	std::cout << "ConcretePrototype copy ..." << std::endl;
}

Prototype_1* ConcretePrototype_1::Clone() const
{
	return new ConcretePrototype_1(*this);
}

int test_Prototype1()
{
	ConcretePrototype1* test1 = new ConcretePrototype1("小王");
	ConcretePrototype2* test2 = (ConcretePrototype2*)test1->Clone();

	test1->Show();
	test2->Show();
	/* result:
		小王
		小王
	*/

	return 0;
}

int test_Prototype2()
{
	Prototype_1* p = new ConcretePrototype_1();
	Prototype_1* p1 = p->Clone();

	/* result:
		ConcretePrototype copy ...
	*/
	return 0;
}
