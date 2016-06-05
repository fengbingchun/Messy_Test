#include <iostream>
#include "product.hpp"

AbstractProductA::AbstractProductA()
{

}

AbstractProductA::~AbstractProductA()
{

}

AbstractProductB::AbstractProductB()
{

}

AbstractProductB::~AbstractProductB()
{

}

ProductA1::ProductA1()
{
	std::cout << "ProductA1 ..." << std::endl;
};

ProductA1::~ProductA1()
{

}

ProductA2::ProductA2()
{
	std::cout << "ProductA2 ..." << std::endl;
}

ProductA2::~ProductA2()
{

}

ProductB1::ProductB1()
{
	std::cout << "ProductB1 ..." << std::endl;
}

ProductB1::~ProductB1()
{

}

ProductB2::ProductB2()
{
	std::cout << "ProductB2 ..." << std::endl;
}

ProductB2::~ProductB2()
{

}