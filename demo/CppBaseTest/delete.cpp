#include "delete.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52475108

//////////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/b-6-new-virtual-function-controls-override-final-default-and-delete/
class Foo
{
	Foo& operator=(const Foo&) = delete; // disallow use of assignment operator
	Foo(const Foo&) = delete; // disallow copy construction
};

class Foo_1
{
	Foo_1(long long); // Can create Foo() with a long long
	Foo_1(long) = delete; // But can't create it with anything smaller
};

class Foo_2
{
	Foo_2(long long); // Can create Foo() with a long long
	template<typename T> Foo_2(T) = delete; // But can't create it with anything else
};

///////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/C11/C11_default_delete_specifier.php
class A_
{
public:
	A_(int a){};
	A_(double) = delete;         // conversion disabled
	A_& operator=(const A_&) = delete;  // assignment operator disabled
};

int test_delete1()
{
	A_ a_(10);     // OK
	// A_ b(3.14);   // Error: conversion from double to int disabled
	// a = b;       // Error: assignment operator disabled

	return 0;
}

////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dn457344.aspx
struct widget
{
	// deleted operator new prevents widget from being dynamically allocated.
	void* operator new(std::size_t) = delete;
};
