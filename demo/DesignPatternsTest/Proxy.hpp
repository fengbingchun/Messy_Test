#ifndef FBC_MESSY_TEST_PROXY_HPP_
#define FBC_MESSY_TEST_PROXY_HPP_

#include <iostream>

//定义接口
class Interface
{
public:
	virtual void Request() = 0;
};

//真实类
class RealClass : public Interface
{
public:
	virtual void Request()
	{
		std::cout << "真实的请求" << std::endl;
	}
};

//代理类
class ProxyClass : public Interface
{
private:
	RealClass* m_realClass;
public:
	virtual void Request()
	{
		m_realClass = new RealClass();
		m_realClass->Request();
		delete m_realClass;
	}
};

// ======================================
class Subject_1
{
public:
	virtual ~Subject_1();
	virtual void Request() = 0;
protected:
	Subject_1();
private:
};

class ConcreteSubject_1 : public Subject_1
{
public:
	ConcreteSubject_1();
	~ConcreteSubject_1();
	void Request();
protected:
private:
};

class Proxy
{
public:
	Proxy();
	Proxy(Subject_1* sub);
	~Proxy();
	void Request();
protected:
private:
	Subject_1* _sub;
};

int test_Proxy1();
int test_Proxy2();

#endif // FBC_MESSY_TEST_PROXY_HPP_
