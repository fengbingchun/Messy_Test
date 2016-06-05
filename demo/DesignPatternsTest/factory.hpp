#ifndef FBC_MESSY_TEST_FACTORY_HPP_
#define FBC_MESSY_TEST_FACTORY_HPP_

class Product_2;

class Factory
{
public:
	virtual ~Factory() = 0;
	virtual Product_2* CreateProduct() = 0;
protected:
	Factory();
private:
};

class ConcreteFactory : public Factory
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product_2* CreateProduct();
protected:
private:
};

#endif // FBC_MESSY_TEST_FACTORY_HPP_