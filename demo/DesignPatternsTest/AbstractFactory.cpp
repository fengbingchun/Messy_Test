#include "AbstractFactory.hpp"
#include "product.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/21872127

AbstractFactory::AbstractFactory()
{

}

AbstractFactory::~AbstractFactory()
{

}

ConcreteFactory1::ConcreteFactory1()
{

}

ConcreteFactory1::~ConcreteFactory1()
{

}

AbstractProductA* ConcreteFactory1::CreateProductA()
{
	return new ProductA1();
}

AbstractProductB* ConcreteFactory1::CreateProductB()
{
	return new ProductB1;
}

ConcreteFactory2::ConcreteFactory2()
{

}

ConcreteFactory2::~ConcreteFactory2()
{

}

AbstractProductA* ConcreteFactory2::CreateProductA()
{
	return new ProductA2();
}

AbstractProductB* ConcreteFactory2::CreateProductB()
{
	return new ProductB2();
}

int test_AbstractFactory1()
{
	IFactory* factory = new SqlFactory();
	IUser* user = factory->CreateUser();
	IDepartment* depart = factory->CreateDepartment();
	user->GetUser();
	depart->GetDepartment();

	/*result:
		Sql GetUser
		Sql GetDepartment
	*/

	return 0;
}

int test_AbstractFactory2()
{
	AbstractFactory* cf1 = new ConcreteFactory1();

	cf1->CreateProductA();
	cf1->CreateProductB();

	AbstractFactory* cf2 = new ConcreteFactory2();

	cf2->CreateProductA();
	cf2->CreateProductB();

	/*result:
		ProductA1 ...
		ProductB1 ...
		ProductA2 ...
		ProductB2 ...
	*/

	return 0;
}
