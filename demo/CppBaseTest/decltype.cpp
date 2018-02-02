#include "decltype.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52504519

//////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/decltype
struct A { double x; };
const A* a = new A{ 0 };

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u); // return type depends on template parameters

int test_decltype1()
{
	int i = 33;
	decltype(i) j = i * 2;

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	auto f = [](int a, int b) -> int
	{
		return a * b;
	};

	decltype(f) g = f; // the type of a lambda function is unique and unnamed
	i = f(2, 2);
	j = g(3, 3);

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd537655.aspx
template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
decltype(std::forward<T1>(t1) +std::forward<T2>(t2))
{
	return std::forward<T1>(t1) +std::forward<T2>(t2);
}

class X
{
	friend X operator+(const X& x1, const X& x2)
	{
		return X(x1.m_data + x2.m_data);
	}

public:
	X(int data) : m_data(data) {}
	int Dump() const { return m_data; }
private:
	int m_data;
};

int test_decltype2()
{
	// Integer 
	int i = 4;
	std::cout << "Plus(i, 9) = " << Plus(i, 9) << std::endl;

	// Floating point
	float dx = 4.0;
	float dy = 9.5;
	std::cout << std::setprecision(3) << "Plus(dx, dy) = " << Plus(dx, dy) << std::endl;

	// String
	std::string hello = "Hello, ";
	std::string world = "world!";
	std::cout << Plus(hello, world) << std::endl;

	// Custom type
	X x1(20);
	X x2(22);
	X x3 = Plus(x1, x2);
	std::cout << "x3.Dump() = " << x3.Dump() << std::endl;

	return 0;
}

///////////////////////////////////////////////////
// reference: http://thbecker.net/articles/auto_and_decltype/section_06.html
struct S {
	S(){ m_x = 42; }
	int m_x;
};

int x;
const int cx = 42;
const int& crx = x;
const S* p = new S();

// x is declared as an int: x_type is int.
typedef decltype(x) x_type;

// auto also deduces the type as int: a_ is an int.
auto a_ = x;

// cx is declared as const int: cx_type is const int.
typedef decltype(cx) cx_type;

// auto drops the const qualifier: b is int.
auto b = cx;

// crx is declared as const int&: crx_type is const int&.
typedef decltype(crx) crx_type;

// auto drops the reference and the const qualifier: c is an int.
auto c = crx;

// S::m_x is declared as int: m_x_type is int
// Note that p->m_x cannot be assigned to. It is effectively
// constant because p is a pointer to const. But decltype goes
// by the declared type, which is int.
typedef decltype(p->m_x) m_x_type;

// auto sees that p->m_x is const, but it drops the const
// qualifier. Therefore, d is an int.
auto d = p->m_x;
