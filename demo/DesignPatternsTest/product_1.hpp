#ifndef FBC_MESSY_TEST_PRODUCT1_HPP_
#define FBC_MESSY_TEST_PRODUCT1_HPP_

class Product_1
{
public:
	Product_1();
	~Product_1();
	void ProducePart();
protected:
private:
};

class ProductPart
{
public:
	ProductPart();
	~ProductPart();
	ProductPart* BuildPart();
protected:
private:
};

#endif // FBC_MESSY_TEST_PRODUCT1_HPP_