#include <iostream>

#include "Factory_1.hpp"

//基类
COperation_1::COperation_1()
{
	m_numA = 0.0;
	m_numB = 0.0;
	std::cout<<"COperation constructor"<<std::endl;
}

COperation_1::~COperation_1()
{
	std::cout<<"COperation destructor"<<std::endl;
}

//加法
CAddOperation_1::CAddOperation_1(double a, double b)
{
	std::cout<<"CAddOperation constructor"<<std::endl;
	m_numA = a;
	m_numB = b;
}

CAddOperation_1::~CAddOperation_1()
{
	std::cout<<"CAddOperation destructor"<<std::endl;
}

double CAddOperation_1::GetResult()
{
	return (m_numA + m_numB);
}

//减法
CSubOperation_1::CSubOperation_1(double a, double b)
{
	std::cout<<"CSubOperation constructor"<<std::endl;
	m_numA = a;
	m_numB = b;
}

CSubOperation_1::~CSubOperation_1()
{
	std::cout<<"CSubOperation destructor"<<std::endl;
}

double CSubOperation_1::GetResult()
{
	return (m_numA - m_numB);
}

//乘法
CMulOperation_1::CMulOperation_1(double a, double b)
{
	std::cout<<"CMulOperation constructor"<<std::endl;
	m_numA = a;
	m_numB = b;
}

CMulOperation_1::~CMulOperation_1()
{
	std::cout<<"CMulOperation destructor"<<std::endl;
}

double CMulOperation_1::GetResult()
{
	return (m_numA * m_numB);
}

//除法
CDivOperation_1::CDivOperation_1(double a, double b)
{
	std::cout<<"CDivOperation constructor"<<std::endl;
	m_numA = a;
	m_numB = b;
}

CDivOperation_1::~CDivOperation_1()
{
	std::cout<<"CDivOperation destructor"<<std::endl;
}

double CDivOperation_1::GetResult()
{
	return (m_numA / m_numB);
}


//工厂类
COperation_1* CCalculatorFactory_1::CreateOperation(PRODUCTTYPE_1 type, double a, double b)
{
	switch (type)
	{
	case 1:
		return new CAddOperation_1(a, b);
		break;
	case 2:
		return new CSubOperation_1(a, b);
		break;
	case 3:
		return new CMulOperation_1(a, b);
		break;
	case 4:
		return new CDivOperation_1(a, b);
		break;
	default:
		return NULL;
	}
}