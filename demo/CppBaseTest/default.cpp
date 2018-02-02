#include "default.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52475155

////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/b-6-new-virtual-function-controls-override-final-default-and-delete/
class Foo
{
	Foo(int x); // Custom constructor
	Foo() = default; // The compiler will now provide a default constructor for class Foo as well
};

/////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/default_constructor
struct A
{
	int x;
	A(int x = 1) : x(x) {} // user-defined default constructor
};

struct B : A
{
	// B::B() is implicitly-defined, calls A::A()
};

struct C
{
	A a;
	// C::C() is implicitly-defined, calls A::A()
};

struct D : A
{
	D(int y) : A(y) {}
	// D::D() is not declared because another constructor exists
};

struct E : A
{
	E(int y) : A(y) {}
	E() = default; // explicitly defaulted, calls A::A()
};

struct F
{
	int& ref; // reference member
	const int c; // const member
	// F::F() is implicitly defined as deleted
};

int test_default1()
{
	A a;
	B b;
	C c;
	// D d; // compile error
	E e;
	// F f; // compile error

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dn457344.aspx
struct widget
{
	widget() = default;

	inline widget& operator=(const widget&);
};

// Notice that you can default a special member function outside the body of a class as long as it¡¯s inlinable.
inline widget& widget::operator=(const widget&) = default;
