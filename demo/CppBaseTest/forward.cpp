#include "forward.hpp"
#include <utility>
#include <iostream>
#include <memory>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52589454

//////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/utility/forward
struct A {
	A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
	A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};

class B {
public:
	template<class T1, class T2, class T3>
	B(T1&& t1, T2&& t2, T3&& t3) :
		a1_{ std::forward<T1>(t1) },
		a2_{ std::forward<T2>(t2) },
		a3_{ std::forward<T3>(t3) }
	{
	}

private:
	A a1_, a2_, a3_;
};

template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
	return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
	return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

int test_forward1()
{
	auto p1 = make_unique1<A>(2); // rvalue
	int i = 1;
	auto p2 = make_unique1<A>(i); // lvalue

	std::cout << "B\n";
	auto t = make_unique<B>(2, i, 3);

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/utility/forward/
// function with lvalue and rvalue reference overloads:
void overloaded(const int& x) { std::cout << "[lvalue]"; }
void overloaded(int&& x) { std::cout << "[rvalue]"; }

// function template taking rvalue reference to deduced type:
template <class T> void fn(T&& x) {
	overloaded(x);                   // always an lvalue
	overloaded(std::forward<T>(x));  // rvalue if argument is rvalue
}

int test_forward2()
{
	int a;

	std::cout << "calling fn with lvalue: ";
	fn(a);
	std::cout << '\n';

	std::cout << "calling fn with rvalue: ";
	fn(0);
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/8526598/how-does-stdforward-work
template<class T>
struct some_struct{
	T _v;
	template<class U>
	some_struct(U&& v) : _v(static_cast<U&&>(v)) {} // perfect forwarding here
	// std::forward is just syntactic sugar for this
};

int test_forward3()
{
	/* remember the reference collapsing rules(引用折叠规则):
	前者代表接受类型，后者代表进入类型，=>表示引用折叠之后的类型，即最后被推导决断的类型
	TR   R

	T&   &->T&   // lvalue reference to cv TR -> lvalue reference to T
	T&   &&->T&  // rvalue reference to cv TR -> TR (lvalue reference to T)
	T&&  &->T&   // lvalue reference to cv TR -> lvalue reference to T
	T&&  &&->T&& // rvalue reference to cv TR -> TR (rvalue reference to T) */

	some_struct<int> s1(5);
	// in ctor: '5' is rvalue (int&&), so 'U' is deduced as 'int', giving 'int&&'
	// ctor after deduction: 'some_struct(int&& v)' ('U' == 'int')
	// with rvalue reference 'v' bound to rvalue '5'
	// now we 'static_cast' 'v' to 'U&&', giving 'static_cast<int&&>(v)'
	// this just turns 'v' back into an rvalue
	// (named rvalue references, 'v' in this case, are lvalues)
	// huzzah, we forwarded an rvalue to the constructor of '_v'!

	// attention, real magic happens here
	int i = 5;
	some_struct<int> s2(i);
	// in ctor: 'i' is an lvalue ('int&'), so 'U' is deduced as 'int&', giving 'int& &&'
	// applying the reference collapsing rules yields 'int&' (& + && -> &)
	// ctor after deduction and collapsing: 'some_struct(int& v)' ('U' == 'int&')
	// with lvalue reference 'v' bound to lvalue 'i'
	// now we 'static_cast' 'v' to 'U&&', giving 'static_cast<int& &&>(v)'
	// after collapsing rules: 'static_cast<int&>(v)'
	// this is a no-op, 'v' is already 'int&'
	// huzzah, we forwarded an lvalue to the constructor of '_v'!

	return 0;
}

////////////////////////////////////////////////////
// reference: https://oopscenities.net/2014/02/01/c11-perfect-forwarding/
void sum(int a, int b)
{
	std::cout << a + b << std::endl;
}

void concat(const std::string& a, const std::string& b)
{
	std::cout<< a + b << std::endl;
}

void successor(int a, int& b)
{
	b = ++a;
}

template <typename PROC, typename A, typename B>
void invoke(PROC p, A&& a, B&& b)
{
	p(std::forward<A>(a), std::forward<B>(b));
}

int test_forward4()
{
	invoke(sum, 10, 20);
	invoke(concat, "Hello", "world");
	int s = 0;
	invoke(successor, 10, s);
	std::cout << s << std::endl;

	return 0;
}
