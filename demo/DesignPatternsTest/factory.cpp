#include <iostream>

#include "factory.hpp"
#include "product_2.hpp"


Factory::Factory()
{

}

Factory::~Factory()
{

}

ConcreteFactory::ConcreteFactory()
{
	std::cout << "ConcreteFactory ..." << std::endl;
}

ConcreteFactory::~ConcreteFactory()
{

}

Product_2* ConcreteFactory::CreateProduct()
{
	return new ConcreteProduct_2();
}
