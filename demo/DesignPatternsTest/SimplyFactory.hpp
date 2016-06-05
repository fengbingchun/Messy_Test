#ifndef FBC_MESSY_TEST_SIMPLY_FACTORY_HPP_
#define FBC_MESSY_TEST_SIMPLY_FACTORY_HPP_

#include <string>
#include <iostream>

typedef enum ProductTypeTag
{
	ADD = 1,
	SUB = 2,
	MUL = 3,
	DIV = 4
}PRODUCTTYPE;

//基类
class COperation
{
public:
	COperation() : m_numA(0.0), m_numB(0.0)
	{
		std::cout << "COperation constructor" << std::endl;
	}

	virtual ~COperation()
	{
		std::cout << "COperation destructor" << std::endl;
	}

	virtual double GetResult() = 0;

protected:
	double m_numA;
	double m_numB;
};

//加法
class CAddOperation : public COperation
{
public:
	CAddOperation(double a, double b)
	{
		std::cout << "CAddOperation constructor" << std::endl;
		m_numA = a;
		m_numB = b;
	}

	virtual ~CAddOperation()
	{
		std::cout << "CAddOperation destructor" << std::endl;
	}

	virtual double GetResult()
	{
		return (m_numA + m_numB);
	}
};

//减法
class CSubOperation : public COperation
{
public:
	CSubOperation(double a, double b)
	{
		std::cout << "CSubOperation constructor" << std::endl;
		m_numA = a;
		m_numB = b;
	}

	virtual ~CSubOperation()
	{
		std::cout << "CSubOperation destructor" << std::endl;
	}

	virtual double GetResult()
	{
		return (m_numA - m_numB);
	}
};

//乘法
class CMulOperation : public COperation
{
public:
	CMulOperation(double a, double b)
	{
		std::cout << "CMulOperation constructor" << std::endl;
		m_numA = a;
		m_numB = b;
	}

	virtual ~CMulOperation()
	{
		std::cout << "CMulOperation destructor" << std::endl;
	}

	virtual double GetResult()
	{
		return (m_numA * m_numB);
	}
};

//除法
class CDivOperation : public COperation
{
public:
	CDivOperation(double a, double b)
	{
		std::cout << "CDivOperation constructor" << std::endl;
		m_numA = a;
		m_numB = b;
	}

	virtual ~CDivOperation()
	{
		std::cout << "CDivOperation destructor" << std::endl;
	}

	virtual double GetResult()
	{
		return (m_numA / m_numB);
	}
};

//工厂类
class CCalculatorFactory
{
public:
	static COperation* CreateOperation(PRODUCTTYPE type, double a, double b)
	{
		switch (type)
		{
		case 1:
			return new CAddOperation(a, b);
			break;
		case 2:
			return new CSubOperation(a, b);
			break;
		case 3:
			return new CMulOperation(a, b);
			break;
		case 4:
			return new CDivOperation(a, b);
			break;
		default:
			return NULL;
		}
	}
};


int test_SimplyFactory1();
int test_SimplyFactory2();

#endif // FBC_MESSY_TEST_SIMPLY_FACTORY_HPP_
