#include "nullptr.hpp"

#include <iostream>
#include <cstddef> // for std::nullptr_t

// Blog: http://blog.csdn.net/fengbingchun/article/details/51793497

///////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/nullptr
template<class F, class A>
void Fwd(F f, A a)
{
	f(a);
}

void g(int* i)
{
	std::cout << "Function g called\n";
}

int test_nullptr1()
{
	g(NULL);           // Fine
	g(0);              // Fine

	Fwd(g, nullptr);   // Fine
	// Fwd(g, NULL);  // ERROR: No function g(int) // error C2664: “void (int *)”: 无法将参数 1 从“int”转换为“int *”

	int length1 = sizeof(NULL); // x64, length1 = 4
	int length2 = sizeof(nullptr); // x64, length2 = 8

	return 0;
}

///////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/4ex65770.aspx
class MyClass {
public:
	int i;
};

int test_nullptr2()
{
	MyClass * pMyClass = nullptr;
	if (pMyClass == nullptr)
		std::cout << "pMyClass == nullptr" << std::endl; // pMyClass == nullptr

	if (pMyClass == 0)
		std::cout << "pMyClass == 0" << std::endl; // pMyClass == 0

	pMyClass = 0;
	if (pMyClass == nullptr)
		std::cout << "pMyClass == nullptr" << std::endl; // pMyClass == nullptr

	if (pMyClass == 0)
		std::cout << "pMyClass == 0" << std::endl; // pMyClass == 0

	return 0;
}

/////////////////////////////////////////////////////
void f(int *)
{
	std::cout << "f(int *)" << std::endl;;
}

void f(int &)
{
	std::cout << "f(int &)" << std::endl;
}

int test_nullptr3()
{
	f(nullptr); // f(int *)
	// try one of the following lines instead
	f((int *) nullptr); // f(int *)
	f(0); // f(int *)
	f(NULL); // f(int *)
	//f((int &) nullptr); // error C2101: 常量上的“&”

	return 0;
}

//////////////////////////////////////////////
// reference: http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
void func(int n)
{
	std::cout << "func (int n)" << std::endl;
}

void func(char *s)
{
	std::cout << "func (char *s)" << std::endl;
}

int test_nullptr4()
{
	func(0); // func (int n)
	func(NULL); // func (int n)
	func(nullptr); // func (char *s)

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/6-7a-null-pointers/
void doSomething(int *ptr)
{
	if (ptr)
		std::cout << "You passed in " << *ptr << '\n';
	else
		std::cout << "You passed in a null pointer\n";
}

void doSomething_(std::nullptr_t ptr)
{
	std::cout << "in doSomething_()\n";
}

int test_nullptr5()
{
	int* a = NULL; // ok
	//int* b = (void*)0; // error C2440: “初始化”: 无法从“void *”转换为“int *”
	int* c = 0; // ok

	// the argument is definitely a null pointer (not an integer)
	doSomething(nullptr); // You passed in a null pointer
	doSomething(0); // You passed in a null pointer
	doSomething(NULL); // You passed in a null pointer

	// call doSomething_ with an argument of type std::nullptr_t
	doSomething_(nullptr); // in doSomething_()

	return 0;
}
