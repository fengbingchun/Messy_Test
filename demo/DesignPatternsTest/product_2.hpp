#ifndef FBC_MESSY_TEST_Product_22_HPP_
#define FBC_MESSY_TEST_Product_22_HPP_

class Product_2
{
public:
	virtual ~Product_2() = 0;
protected:
	Product_2();
private:
};

class ConcreteProduct_2 : public Product_2
{
public:
	~ConcreteProduct_2();
	ConcreteProduct_2();

protected:
private:
};

#endif // FBC_MESSY_TEST_Product_22_HPP_