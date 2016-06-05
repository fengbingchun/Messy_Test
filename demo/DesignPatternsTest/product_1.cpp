#include "product_1.hpp"
#include <iostream>


Product_1::Product_1()
{
	ProducePart();
	std::cout << "return a product" << std::endl;
}

Product_1::~Product_1()
{

}

void Product_1::ProducePart()
{
	std::cout << "build part of product ..." << std::endl;
}

ProductPart::ProductPart()
{
	std::cout << "build productpart ..." << std::endl;
}

ProductPart::~ProductPart()
{

}

ProductPart* ProductPart::BuildPart()
{
	return new ProductPart;
}
