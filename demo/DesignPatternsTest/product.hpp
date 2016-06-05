#ifndef FBC_MESSY_TEST_PRODUCT_HPP_
#define FBC_MESSY_TEST_PRODUCT_HPP_

class AbstractProductA
{
public:
	virtual ~AbstractProductA();

protected:
	AbstractProductA();

private:
};

class AbstractProductB
{
public:
	virtual ~AbstractProductB();

protected:
	AbstractProductB();

private:
};

class ProductA1 : public AbstractProductA
{
public:
	ProductA1();
	~ProductA1();

protected:
private:
};

class ProductA2 : public AbstractProductA
{
public:
	ProductA2();
	~ProductA2();

protected:
private:
};

class ProductB1 : public AbstractProductB
{
public:
	ProductB1();
	~ProductB1();

protected:
private:
};

class ProductB2 : public AbstractProductB
{
public:
	ProductB2();
	~ProductB2();

protected:
private:
};

#endif // FBC_MESSY_TEST_PRODUCT_HPP_
