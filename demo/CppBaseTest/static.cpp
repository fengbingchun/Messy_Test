#include "static.hpp"
#include <iostream>

// Blog: https://blog.csdn.net/fengbingchun/article/details/80874852

namespace static_ {

///////////////////////////////////////////////////////////
static size_t count_calls()
{
	// 局部静态对象(local static object)在程序的执行路径第一次经过对象定义
	// 语句时初始化,并且直到程序终止才被销毁，在此期间即使对象所在的函数结
	// 束执行也不会对它有影响。
	static size_t ctr = 0; // 调用结束后，这个值仍然有效
	return ++ctr;
}

int test_static_1()
{
	for (int i = 0; i < 10; ++i) {
		fprintf(stdout, "ctr: %d\n", count_calls());
	}

	return 0;
}

/////////////////////////////////////////////////////////////
int A::val = 10;
int A::val3 = 15;

int A::func()
{
	return ++val3;
}

int A::func2()
{
	return (val3 + val2 + func());
}

int test_static_2()
{
	fprintf(stdout, "A::val: %d\n", A::val);
	for (int i = 0; i < 5; ++i)
		fprintf(stdout, "A::func: %d\n", A::func());

	A a;
	fprintf(stdout, "a.func2: %d\n", a.func2());

	return 0;
}

////////////////////////////////////////////////////////////////
static int xx = 5;

int test_static_3()
{
	fprintf(stdout, "xx: %d\n", xx);

	return 0;
}

///////////////////////////////////////////////////////////////////
// reference: https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr039.htm
int X::si = 77; // Initialize static data member

int test_static_4()
{
	X xobj;
	xobj.set_i(11);
	xobj.print_i();

	// static data members and functions belong to the class and
	// can be accessed without using an object of class X
	X::print_si();
	X::set_si(22);
	X::print_si();

	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr039.htm
void C::printall() {
	std::cout << "Here is j: " << this->j << std::endl;
	// You can call a static member function using the this pointer of a nonstatic member function
	this->f();
}

int C::i = 3;

int test_static_5()
{
	C obj_C(2);
	obj_C.printall();

	return 0;
}

/////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/y5f6w579.aspx
void showstat(int curr)
{
	static int nStatic; // Value of nStatic is retained between each function call
	nStatic += curr;
	std::cout << "nStatic is " << nStatic << std::endl;
}

int test_static_6()
{
	for (int i = 0; i < 5; i++)
		showstat(i);

	return 0;
}

///////////////////////////////////////////////////
Singleton::Singleton()
{
	std::cout << "constructor Singleton ..." << std::endl;
}

Singleton& Singleton::Instance()
{
	static Singleton _instance;
	return _instance;
}

int test_static_7()
{
	Singleton& sgn1 = Singleton::Instance();
	Singleton& sgn2 = Singleton::Instance();

	if (&sgn1 == &sgn2) std::cout << "ok" << std::endl;
	else std::cout << "no" << std::endl;

	return 0;
}

} // namespace static_
