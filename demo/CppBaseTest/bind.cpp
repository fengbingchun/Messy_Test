#include "bind.hpp"
#include <iostream>
#include <string>
#include <functional> // std::bind
#include <random>
#include <memory>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52653313

//////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/utility/functional/bind
static void f(int n1, int n2, int n3, const int& n4, int n5)
{
	std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

static int g(int n1)
{
	return n1;
}

struct Foo_bind {
	void print_sum(int n1, int n2)
	{
		std::cout << n1 + n2 << '\n';
	}
	int data = 10;
};

int test_bind1()
{
	using namespace std::placeholders;  // for _1, _2, _3...

	// demonstrates argument reordering and pass-by-reference
	int n = 7;
	// (_1 and _2 are from std::placeholders, and represent future
	// arguments that will be passed to f1)
	auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
	n = 10;
	f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
	// makes a call to f(2, 1, 42, n, 7)

	// nested bind subexpressions share the placeholders
	auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
	f2(10, 11, 12);

	// common use case: binding a RNG with a distribution
	std::default_random_engine e;
	std::uniform_int_distribution<> d(0, 10);
	std::function<int()> rnd = std::bind(d, e); // a copy of e is stored in rnd
	for (int n = 0; n<10; ++n)
		std::cout << rnd() << ' ';
	std::cout << '\n';

	// bind to a pointer to member function
	Foo_bind foo;
	auto f3 = std::bind(&Foo_bind::print_sum, &foo, 95, _1);
	f3(5);

	// bind to a pointer to data member
	auto f4 = std::bind(&Foo_bind::data, _1);
	std::cout << f4(foo) << '\n';

	// smart pointers can be used to call members of the referenced objects, too
	//std::cout << f4(std::make_shared<Foo_bind>(foo)) << '\n'
	//	<< f4(std::make_unique<Foo_bind>(foo)) << '\n';

	return 0;
}

///////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/functional/bind/
// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide(double x, double y) { return x / y; }

struct MyPair {
	double a, b;
	double multiply() { return a*b; }
};

int test_bind2()
{
	using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

	// binding functions:
	auto fn_five = std::bind(my_divide, 10, 2);               // returns 10/2
	std::cout << fn_five() << '\n';                          // 5

	auto fn_half = std::bind(my_divide, _1, 2);               // returns x/2
	std::cout << fn_half(10) << '\n';                        // 5

	auto fn_invert = std::bind(my_divide, _2, _1);            // returns y/x
	std::cout << fn_invert(10, 2) << '\n';                    // 0.2

	auto fn_rounding = std::bind<int>(my_divide, _1, _2);     // returns int(x/y)
	std::cout << fn_rounding(10, 3) << '\n';                  // 3

	MyPair ten_two{ 10, 2 };

	// binding members:
	auto bound_member_fn = std::bind(&MyPair::multiply, _1); // returns x.multiply()
	std::cout << bound_member_fn(ten_two) << '\n';           // 20

	auto bound_member_data = std::bind(&MyPair::a, ten_two); // returns ten_two.a
	std::cout << bound_member_data() << '\n';                // 10

	return 0;
}

/////////////////////////////////////////////////
// reference: https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/
static void show(const std::string& a, const std::string& b, const std::string& c)
{
	std::cout << a << "; " << b << "; " << c << std::endl;
}

int test_bind3()
{
	using namespace std::placeholders;

	// Thanks to the placeholders, you can change the order of the arguments passed as parameters to a bound function.
	auto x = bind(show, _1, _2, _3);
	auto y = bind(show, _3, _1, _2);
	auto z = bind(show, "hello", _2, _1);

	x("one", "two", "three");
	y("one", "two", "three");
	z("one", "two");

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/22422147/why-is-stdbind-not-working-without-placeholders-in-this-example-member-functi
static void f_(int a, int b, int c)
{
	fprintf(stdout, "a = %d, b = %d, c = %d\n", a, b, c);
}

struct foo_bind
{
	void f() const { fprintf(stdout, "foo_bind\n"); };
};

int test_bind4()
{
	using namespace std::placeholders;

	// The first parameter of std::bind() is the function to be called, and the rest are the arguments of the call.
	std::function<void()> f_call = std::bind(f_, 1, 2, 3);
	f_call(); //Equivalent to f_(1,2,3)

	// If you need to specify that some parameters have to be specified at the call point,
	// you have to use placeholders to represent that parameters
	std::function<void(int, int, int)> f_call2 = std::bind(f_, _1, _2, _3);
	f_call2(1, 2, 3); //Same as f_(1,2,3)

	// Note that the numbers of the placeholders specify the number of the parameter at the call point.
	// The first parameter of the call point is identified by _1, the second by _2, and so on.
	// This could be used to specify parameters in different ways, reordering the parameters of a function call, etc.
	std::function<void(int, int)> f_call3 = std::bind(f_, _1, 2, _2);
	f_call3(1, 3); //Equivalent to f_( 1 , 2 , 3 );

	std::function<void(int, int, int)> reordered_call = std::bind(f_, _3, _2, _1);
	reordered_call(3, 2, 1); //Same as f_( 1 , 2 , 3 );

	// std::bind() could be used to bind a member function to the object used to call it
	foo_bind myfoo;
	std::function<void()> f = std::bind(&foo_bind::f, std::cref(myfoo));
	f();

	return 0;
}

/////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/bb982702.aspx
static void square(double x)
{
	std::cout << x << "^2 == " << x * x << std::endl;
}

static void product(double x, double y)
{
	std::cout << x << "*" << y << " == " << x * y << std::endl;
}

int test_bind5()
{
	using namespace std::placeholders;

	double arg[] = { 1, 2, 3 };

	std::for_each(&arg[0], arg + 3, square);
	std::cout << std::endl;

	std::for_each(&arg[0], arg + 3, std::bind(product, _1, 2));
	std::cout << std::endl;

	std::for_each(&arg[0], arg + 3, std::bind(square, _1));

	return (0);
}
