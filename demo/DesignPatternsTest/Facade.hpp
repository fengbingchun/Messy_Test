#ifndef FBC_MESSY_TEST_FACADE_HPP_
#define FBC_MESSY_TEST_FACADE_HPP_

#include <iostream>

class SubSysOne
{
public:
	void MethodOne()
	{
		std::cout << "方法一" << std::endl;
	}
};

class SubSysTwo
{
public:
	void MethodTwo()
	{
		std::cout << "方法二" << std::endl;
	}
};

class SubSysThree
{
public:
	void MethodThree()
	{
		std::cout << "方法三" << std::endl;
	}
};

//外观类
class Facade
{
private:
	SubSysOne* sub1;
	SubSysTwo* sub2;
	SubSysThree* sub3;
public:
	Facade()
	{
		sub1 = new SubSysOne();
		sub2 = new SubSysTwo();
		sub3 = new SubSysThree();
	}

	~Facade()
	{
		delete sub1;
		delete sub2;
		delete sub3;
	}

	void FacadeMethod()
	{
		sub1->MethodOne();
		sub2->MethodTwo();
		sub3->MethodThree();
	}
};

// ================================================
class Subsystem1
{
public:
	Subsystem1();
	~Subsystem1();
	void Operation();
protected:
private:
};

class Subsystem2
{
public:
	Subsystem2();
	~Subsystem2();
	void Operation();
protected:
private:
};

class Facade_1
{
public:
	Facade_1();
	~Facade_1();
	void OperationWrapper();
protected:
private:
	Subsystem1* _subs1;
	Subsystem2* _subs2;
};

int test_Facade1();
int test_Facade2();

#endif // FBC_MESSY_TEST_FACADE_HPP_
